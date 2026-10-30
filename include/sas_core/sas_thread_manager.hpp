/*
# Copyright (c) 2012-2026 Murilo Marques Marinho
#
#    This file is part of sas_core.
#
#    sas_core is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    sas_core is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with sas_core.  If not, see <https://www.gnu.org/licenses/>.
*/

// Compatibility shim: the C++ core now lives in the libmarinholab-sas-core
// .deb (MarinhoLab/sas_cpp). Preserves the legacy #include <sas_core/sas_thread_manager.hpp>
// path and the legacy "namespace sas" used by downstream packages.
#pragma once
#include <marinholab/sas/core/sas_thread_manager.hpp>

namespace sas
{
    using namespace marinholab::sas::core;
}
