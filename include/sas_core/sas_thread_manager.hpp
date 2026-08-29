/*
# Copyright (c) 2022-2026 Murilo Marques Marinho
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
#   Author: Juan Jose Quiroz Omana, email: juanjose.quirozomana@manchester.ac.uk
#
# ################################################################*/

#pragma once
#include <sas_core/sas_core.hpp>
#include <sas_core/sas_clock.hpp>
#include <functional>
#include <thread>
#include <atomic>
#include <string>

namespace sas
{

class thread_manager
{
public:
    // PRIORITY levels
    enum class PRIORITY {
        LOWEST = 0,
        BACKGROUND = 10,
        NORMAL = 50,
        HIGH = 80,
        REALTIME = 90,
        CRITICAL = 99
    };



private:
    // Thread optimization parameters
    PRIORITY priority_{PRIORITY::NORMAL};
    int cpu_core_{-1};
    void apply_priority();
    void apply_cpu_affinity();


protected:
    sas::Clock clock_;
    std::function<void()> loop_callback_;
    std::thread thread_;
    std::string thread_name_;
    std::atomic<bool> running_{false};
    std::atomic<bool> stop_requested_{false};

protected:
    void run();
public:
    ~thread_manager();

    thread_manager(const thread_manager&) = delete;            // Copy constructor
    thread_manager& operator=(const thread_manager&) = delete; // Copy assignment
    thread_manager(thread_manager&&) = delete;                 // Move constructor
    thread_manager& operator=(thread_manager&&) = delete;      // Move assignment

    thread_manager(const std::string& thread_name,
                   const double& period,
                   std::function<void()> callback,
                   PRIORITY priority = PRIORITY::NORMAL,
                   int cpu_core = -1);



    // Performance monitoring using sas::Clock
    double get_computation_time() const;
    double get_sleep_time() const;
    double get_effective_sampling_time() const;
    double get_elapsed_time_sec() const;
    long   get_overrun_count() const;

    // Statistics from sas::Clock
    double get_statistics(const Statistics& statistics,
                          const sas::Clock::TimeType& time_type) const;

    // Lifecycle
    void start();
    void stop();
    bool is_running() const;


    // Getters
    std::string get_thread_name() const;
    PRIORITY get_priority() const;
    int get_cpu_core() const;
    double get_period() const;
};

}

