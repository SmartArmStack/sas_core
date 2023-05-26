#pragma once
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

#include <atomic>
#include <chrono>
#include <map>

#include <sas_core/sas_object.hpp>
#include <sas_core/sas_core.hpp>

namespace sas
{

class Clock : private sas::Object
{
public:
    enum class TimeType{
        Computational,
        EffectiveSampling,
        Idle
    };
private:

    // https://stackoverflow.com/questions/65397041/apple-clang-why-can-i-not-create-a-time-point-from-stdchrononanoseconds
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> time_initial_;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> next_loop_deadline_;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> time_before_sleep_;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> time_after_sleep_;

    const std::chrono::nanoseconds target_sampling_time_;

    std::map<TimeType,std::chrono::nanoseconds> kept_times_map_;
    //Formely
    //std::chrono::nanoseconds loop_duration_;
    //std::chrono::nanoseconds computation_duration_;
    //std::chrono::nanoseconds sleep_duration_;

    long overrun_sampling_time_count_;

    const bool enable_statistics_;

    std::map<std::tuple<TimeType,Statistics>,std::tuple<std::chrono::nanoseconds,long>> statistics_map_;
    void _compute_statistics_();

public:

    Clock()=delete;
    Clock(const int&)=delete;

    explicit Clock(const double& sampling_time_in_seconds, const bool& enable_statistics=true);

    void init();
    void update_and_sleep();
    double get_elapsed_time_sec() const;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> get_initial_time() const;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> get_last_update_time() const;

    void safe_sleep_seconds(const double& seconds, std::atomic_bool* break_loop);
    void blocking_sleep_seconds(const double& seconds);

    double get_computation_time() const;
    double get_sleep_time() const;
    double get_effective_thread_sampling_time_sec() const;

    double get_desired_thread_sampling_time_sec() const;

    long get_overrun_count() const;

    double get_time(const TimeType& time_type) const;
    double get_statistics(const Statistics &statistics, const TimeType &time_type) const;
};

}




