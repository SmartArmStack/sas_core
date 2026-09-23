// Compatibility shim: the C++ core now lives in the libmarinholab-sas-core
// .deb (MarinhoLab/sas_cpp). Preserves the legacy #include <sas_core/sas_clock.hpp>
// path and the legacy "namespace sas" used by downstream packages.
#pragma once
#include <marinholab/sas/core/sas_clock.hpp>

namespace sas
{
    using namespace marinholab::sas::core;
    // `Clock` must be a *real member* of namespace sas (a using-declaration),
    // not merely findable via the using-directive above. Otherwise a downstream
    // package that also does `using namespace rclcpp;` sees a bare `Clock`
    // reference as ambiguous between marinholab::sas::core::Clock and
    // rclcpp::Clock (name lookup through the directive finds both). Declaring
    // it here shadows rclcpp::Clock, matching the old monolithic sas_core where
    // `namespace sas` had its own `class Clock`.
    using Clock = marinholab::sas::core::Clock;
}
