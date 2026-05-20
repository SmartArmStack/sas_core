/*
# Copyright (c) 2016-2023 Murilo Marques Marinho
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
#
# ################################################################
#
#   Author: Murilo M. Marinho, email: murilomarinho@ieee.org
#
# ################################################################*/

#include "sas_core_py.hpp"
#include <sas_core/sas_clock.hpp>
#include <sas_core/sas_shutdown_signaler.hpp>

using C = sas::Clock;
using SS = sas::ShutdownSignaler;

PYBIND11_MODULE(_sas_core, m) {

    sas::init_sas_robot_driver_py(m);

    py::enum_<sas::Statistics>(m, "Statistics")
            .value("Mean",    sas::Statistics::Mean);

    py::class_<SS, py::smart_holder> shutdown_signaler(m,"ShutdownSignaler");
    shutdown_signaler.def(py::init<>());
    shutdown_signaler.def("should_shutdown", &SS::should_shutdown, "");
    shutdown_signaler.def("shutdown", &SS::shutdown, "");

    py::class_<C, py::smart_holder> clock(m, "Clock");

    clock.def(py::init<double>());
    clock.def("init",&C::init,"Initialize clock.");
    clock.def("update_and_sleep",&C::update_and_sleep,"Sleeps only the time necessary to keep the desired rate.");
    clock.def("get_elapsed_time_sec",&C::get_elapsed_time_sec,"Gets the elapsed time in seconds.");
    clock.def("get_desired_thread_sampling_time_sec",&C::get_desired_thread_sampling_time_sec,"Gets the desired sampling time in seconds.");

    ///std::chrono time points, not sure what to do with/about these
    //std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> get_initial_time() const;
    //std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> get_last_update_time() const;

    clock.def("safe_sleep_seconds",&C::safe_sleep_seconds);
    clock.def("blocking_sleep_seconds",&C::blocking_sleep_seconds);

    ///OLD API, no need to expose it
    //double get_computation_time() const;
    //double get_sleep_time() const;
    //double get_effective_thread_sampling_time_sec() const;

    clock.def("get_overrun_count",&C::get_overrun_count);
    clock.def("get_time",&C::get_time);
    clock.def("get_statistics",&C::get_statistics);

    py::enum_<C::TimeType>(clock, "TimeType")
            .value("Computational", C::TimeType::Computational)
            .value("EffectiveSampling", C::TimeType::EffectiveSampling)
            .value("Idle", C::TimeType::Idle)
            .export_values();

}
