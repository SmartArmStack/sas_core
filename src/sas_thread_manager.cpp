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

#include <sas_core/sas_thread_manager.hpp>
#include <stdexcept>
#include <cstring>

#ifdef __linux__
#include <pthread.h>
#endif

namespace sas
{

/**
 * @brief Constructor for thread_manager
 * @param thread_name Name of the thread for identification
 * @param period Period in seconds between callback executions
 * @param callback Function to call periodically
 */
thread_manager::thread_manager(const std::string& thread_name,
                               const double& period,
                               std::function<void()> callback)
    :clock_{period},
    loop_callback_{std::move(callback)},
    thread_name_{thread_name},
    running_{false},
    stop_requested_{false}
{
    if (period <= 0.0) {
        throw std::invalid_argument("thread_manager: period must be positive");
    }
}

/**
 * @brief thread_manager::~thread_manager destructor of the class
 */
thread_manager::~thread_manager()
{
    stop();
}


/**
 * @brief Start the thread execution
 */
void thread_manager::start()
{
    // Atomically set running_ to true and get the previous value.
    if (running_.exchange(true)) {
        return; // Already running - don't start another thread
    }

    // If we get here, running_ was false before. We can safely start the thread.

    stop_requested_ = false;
    clock_.init();
    thread_ = std::thread(&thread_manager::run, this);
}

/**
 * @brief Stop the thread execution and wait for completion
 */
void thread_manager::stop()
{
    if (!running_.exchange(false)) {
        return; // Not running
    }

    stop_requested_ = true;
    if (thread_.joinable()) {
        thread_.join();
    }
}


/**
 * @brief Check if the thread is currently running
 * @return true if running, false otherwise
 */
bool thread_manager::is_running() const
{
    // Returns the current value of running_ in thread-safe way.
    return running_.load();
}


/**
 * @brief Get the thread name
 * @return Thread name string
 */
std::string thread_manager::get_thread_name() const
{
    return thread_name_;
}


/**
 * @brief Main thread entry function
 */
void thread_manager::run()
{
    // Set thread name (if supported by platform)
#ifdef __linux__
    // pthread_setname_np has a 16 character limit (including null terminator)
    std::string truncated_name = thread_name_;
    if (truncated_name.length() > 15) {
        truncated_name.resize(15);
    }
    pthread_setname_np(pthread_self(), truncated_name.c_str());
#endif

    // Main loop
    while (!stop_requested_.load()) {
        // Execute callback
        if (loop_callback_) {
            loop_callback_();
        }
        // Wait for next cycle
        clock_.update_and_sleep();;
    }
}



}
