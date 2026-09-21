// Compatibility shim: the C++ core now lives in the libmarinholab-sas-core
// .deb (MarinhoLab/sas_cpp). Preserves the legacy #include <sas_core/eigen3_std_conversions.hpp>
// path and the legacy "namespace sas" used by downstream packages.
#pragma once
#include <marinholab/sas/core/eigen3_std_conversions.hpp>

namespace sas
{
    using namespace marinholab::sas::core;
}
