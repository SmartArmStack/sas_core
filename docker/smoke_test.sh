#!/usr/bin/env bash
# Integration smoke test for the sas_core thin wrapper.
#
# Runs inside the docker environment provided by docker/compose.yml:
#   [1/3] colcon build of the wrapper package
#   [2/3] Python shim smoke test (sas_core -> marinholab.sas.core)
#   [3/3] C++ compatibility-header consumer compiled against the installed
#         libmarinholab_sas_core (legacy include path + namespace sas)
set -e

cd /root/sas_core_devel/src/

echo '=== [1/3] colcon build (thin wrapper) ==='
colcon build

echo '=== [2/3] Python shim smoke test ==='
source install/setup.bash
python3 sas_core/scripts/sas_core_smoke_test.py

echo '=== [3/3] C++ compatibility header + installed library test ==='
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

echo '=== ALL CHECKS PASSED ==='
