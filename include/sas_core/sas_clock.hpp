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
