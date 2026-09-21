// Compatibility shim: the C++ core now lives in the libmarinholab-sas-core
// .deb (MarinhoLab/sas_cpp). Preserves the legacy #include <sas_core/sas_robot_driver.hpp>
// path and the legacy "namespace sas" used by downstream packages.
#pragma once
#include <marinholab/sas/core/sas_robot_driver.hpp>

namespace sas
{
    using namespace marinholab::sas::core;
}
