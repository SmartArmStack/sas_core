#!/usr/bin/env bash
# Integration smoke test for the sas_core thin wrapper.
#
# Runs inside the docker environment provided by docker/compose.yml:
#   [1/4] colcon build of the wrapper package
#   [2/4] Python shim smoke test (sas_core -> marinholab.sas.core)
#   [3/4] C++ compatibility-header consumer compiled against the installed
#         libmarinholab_sas_core (legacy include path + namespace sas)
#   [4/4] C++ namespace-ambiguity regression test (downstream-style consumer
#         with `using namespace rclcpp;` + bare `Clock` in `namespace sas`)
set -e

cd /root/sas_core_devel/src/

echo '=== [1/4] colcon build (thin wrapper) ==='
colcon build

echo '=== [2/4] Python shim smoke test ==='
source install/setup.bash
python3 sas_core/scripts/sas_core_smoke_test.py

echo '=== [3/4] C++ compatibility header + installed library test ==='
# Wrapper-installed compat headers and the .deb-installed shared library.
SAS_INC=/root/sas_core_devel/src/install/sas_core/include
LIBDIR="$(dirname "$(ldconfig -p | awk '/libmarinholab_sas_core\.so/ {print $NF; exit}')")"
echo "using headers: ${SAS_INC}"
echo "using library: ${LIBDIR}"

cat > /tmp/sas_core_compat_test.cpp <<'CPP'
#include <sas_core/sas_clock.hpp>
#include <iostream>

int main()
{
    sas::Clock c(0.01);
    c.init();
    c.update_and_sleep();
    std::cout << "C++ compat OK, elapsed=" << c.get_elapsed_time_sec() << std::endl;
    return 0;
}
CPP

g++ /tmp/sas_core_compat_test.cpp -o /tmp/sas_core_compat_test \
    -I"${SAS_INC}" -L"${LIBDIR}" -lmarinholab_sas_core \
    -Wl,-rpath,"${LIBDIR}"
/tmp/sas_core_compat_test

echo '=== [4/4] C++ namespace-ambiguity regression test (downstream-style) ==='
# Reproduces SmartArmStack/smart_arm_stack_ROS2 PPA build failure:
# a downstream package does `using namespace rclcpp;` and declares a bare
# `Clock` inside `namespace sas`. With the thin wrapper's using-directive
# shim, `Clock` was ambiguous between rclcpp::Clock and
# marinholab::sas::core::Clock. The `using Clock = ...` declaration in the
# shim makes it a real member of `namespace sas`, shadowing rclcpp::Clock.
# Compile-only: linking the full rclcpp runtime here is not required for
# the name-lookup check.
cat > /tmp/sas_core_ambig_test.cpp <<'CPP'
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sas_core/sas_clock.hpp>

using namespace rclcpp;

namespace sas
{
class Consumer
{
private:
    std::shared_ptr<Node> node_;  // must resolve to rclcpp::Node
    Clock clock_;                 // must resolve to marinholab::sas::core::Clock
public:
    void use()
    {
        clock_.init();            // core Clock::init()
        (void)node_;
    }
};
}

int main()
{
    return 0;
}
CPP

g++ /tmp/sas_core_ambig_test.cpp -c -o /tmp/sas_core_ambig_test.o \
    -I"${SAS_INC}"
echo 'Ambiguity regression test compiled (no ambiguous Clock).'

echo '=== ALL CHECKS PASSED ==='
