// Compatibility shim: the C++ core now lives in the libmarinholab-sas-core
// .deb (MarinhoLab/sas_cpp). Preserves the legacy #include path and namespace.
#pragma once
#include <marinholab/sas/core/examples/sas_robot_driver_example.hpp>

namespace sas
{
    using namespace marinholab::sas::core;
}
