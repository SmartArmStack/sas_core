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

    // Module docstring (Doxygen-style tags included for downstream extraction)
    m.doc() = R"pbdoc(
@file _sas_core
@brief Python bindings for core utilities (Clock, ShutdownSignaler, RobotDriver classes).
)pbdoc";

    sas::init_sas_robot_driver_py(m);

    py::enum_<sas::Statistics>(m, "Statistics", R"pbdoc(@brief Statistic types used by the Clock class.

Currently only `Mean` is supported and it is used by Clock when statistics
collection is enabled.)pbdoc")
            .value("Mean",    sas::Statistics::Mean)
            .export_values();

    py::class_<SS, py::smart_holder> shutdown_signaler(m, "ShutdownSignaler",
        R"pbdoc(@brief Cross-module shutdown signaling class.

ShutdownSignaler coordinates shutdown requests between different parts of the
system.)pbdoc");
    shutdown_signaler.def(py::init<>(), R"pbdoc(@brief Construct a ShutdownSignaler.

Creates a ShutdownSignaler to coordinate shutdown
requests between threads.)pbdoc");
    shutdown_signaler.def("should_shutdown", &SS::should_shutdown, R"pbdoc(@brief Check whether a shutdown has been requested.

@return True if a shutdown has been requested (internal or external), False otherwise.)pbdoc");
    shutdown_signaler.def("shutdown", &SS::shutdown, R"pbdoc(@brief Trigger a shutdown request.

Callers must wait on `should_shutdown()` to observe the change.)pbdoc");

    py::class_<C, py::smart_holder> clock(m, "Clock",
        R"pbdoc(@brief Timing utilities for control loops and statistics collection.)pbdoc");

    clock.def(py::init<double>(), R"pbdoc(@brief Construct a Clock.

@param sampling_time_in_seconds Desired sampling time (seconds).)pbdoc");
    clock.def("init", &C::init, R"pbdoc(@brief Initialize the clock internal state and timers.

Call once before using the clock to set the initial reference time.)pbdoc");
    clock.def("update_and_sleep", &C::update_and_sleep, R"pbdoc(@brief Update internal timing measurements and sleep to respect the target sampling time.

This records the computation time since the last update, computes the next
deadline and sleeps until that deadline. If statistics collection is enabled
the internal statistics are updated.)pbdoc");
    clock.def("get_elapsed_time_sec", &C::get_elapsed_time_sec, R"pbdoc(@brief Get elapsed time since initialization.

@return Elapsed time in seconds since the clock was initialized via `init()`.)pbdoc");
    clock.def("get_desired_thread_sampling_time_sec", &C::get_desired_thread_sampling_time_sec, R"pbdoc(@brief Get the configured sampling interval.

@return Desired sampling time in seconds as configured at construction.)pbdoc");

    // std::chrono time points are not bound to Python here (returned types are C++ types)

    clock.def("safe_sleep_seconds", &C::safe_sleep_seconds, R"pbdoc(@brief Sleep for approximately the given duration while allowing early exit.

@param seconds Duration in seconds to sleep.
@param break_loop Optional pointer to an atomic boolean (C++ side) used to interrupt the sleep early. If `None` is passed from Python it will behave as a blocking sleep loop.)pbdoc");
    clock.def("blocking_sleep_seconds", &C::blocking_sleep_seconds, R"pbdoc(@brief Block the calling thread for the specified duration (no early exit).

@param seconds Duration in seconds to block.)pbdoc");

    clock.def("get_overrun_count", &C::get_overrun_count, R"pbdoc(@brief Return the number of times the sampling period has been missed (overrun).

@return Overrun count as a long integer.)pbdoc");
    clock.def("get_time", &C::get_time, R"pbdoc(@brief Get a time measurement for a given TimeType.

@param time_type One of Clock.TimeType (Computational, EffectiveSampling, Idle).
@return Time value in seconds corresponding to the requested type.)pbdoc");
    clock.def("get_statistics", &C::get_statistics, R"pbdoc(@brief Get a collected statistic value.

@param statistics The statistic type to query (see `sas.Statistics`).
@param time_type The Clock.TimeType to which the statistic applies.
@return The requested statistic value as a double.

@throw RuntimeError If statistics collection was not enabled at construction
      or if the requested statistic is not available.)pbdoc");

    py::enum_<C::TimeType>(clock, "TimeType", R"pbdoc(@brief Enumeration of time types recorded by Clock.

Values:
- Computational: Time spent computing between updates.
- EffectiveSampling: Computational + Idle time between updates.
- Idle: Time spent sleeping between updates.)pbdoc")
            .value("Computational", C::TimeType::Computational)
            .value("EffectiveSampling", C::TimeType::EffectiveSampling)
            .value("Idle", C::TimeType::Idle)
            .export_values();

}
