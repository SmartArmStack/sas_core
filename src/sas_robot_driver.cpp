/*
# Copyright (c) 2016-2025 Murilo Marques Marinho
#
#    This file is part of sas_robot_driver.
#
#    sas_robot_driver is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    sas_robot_driver is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with sas_robot_driver.  If not, see <https://www.gnu.org/licenses/>.
#
# ################################################################
#
#   Author: Murilo M. Marinho, email: murilomarinho@ieee.org
#
# ################################################################# Contributors:
#
#   1. Juan Jose Quiroz Omana (juanjose.quirozomana@manchester.ac.uk)
#      Added the Watchdog functionality initially proposed in
#      https://github.com/SmartArmStack/sas_core/pull/1
*/


#include <sas_core/sas_robot_driver.hpp>
#include <sas_core/sas_clock.hpp>

namespace sas
{

RobotDriver::RobotDriver(std::atomic_bool *break_loops):
    break_loops_(break_loops)
{

}

VectorXd RobotDriver::get_joint_velocities()
{
    throw std::runtime_error("Not implemented yet.");
}

void RobotDriver::set_target_joint_velocities(const VectorXd&)
{
    throw std::runtime_error("Not implemented yet.");
}

VectorXd RobotDriver::get_joint_torques()
{
    throw std::runtime_error("Not implemented yet.");
}

void RobotDriver::set_target_joint_torques(const VectorXd &)
{
    throw std::runtime_error("Not implemented yet.");
}

std::tuple<VectorXd, VectorXd> RobotDriver::get_joint_limits()
{
    return joint_limits_;
}

void RobotDriver::set_joint_limits(const std::tuple<VectorXd, VectorXd> &joint_limits)
{
    joint_limits_ = joint_limits;
}


/**
 * @brief RobotDriver::_watchdog_thread_function throws an exception if the elapsed time since the last trigger
 *        exceeds the specified period.
 */
void RobotDriver::_watchdog_thread_function()
{
    const double& period =  clock_->get_desired_thread_sampling_time_sec();
    clock_->init();
    while(!(*break_loops_))
    {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        double elapsed_time;
        bool wstatus;
        {
            std::scoped_lock lock(mutex_watchdog_);
            elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - last_trigger_).count();
            wstatus = watchdog_status_;
        }
        if (elapsed_time > period)
            throw std::runtime_error(
                std::string("RobotDriver:: The watchdog signal was lost! ") +
                "The elapsed time was " + std::to_string(elapsed_time) +
                " but the period is: " + std::to_string(period)
                );

        if(!wstatus)
            throw std::runtime_error("RobotDriver:: The watchdog status is false!");
        clock_->update_and_sleep();
    }
}

/**
 * @brief RobotDriver::watchdog_start starts the watchdog thread
 * @param period The period of time.
 */
void RobotDriver::watchdog_start(const std::chrono::nanoseconds& period)
{
    if (!clock_)
        clock_ = std::make_unique<sas::Clock>(std::chrono::duration_cast<std::chrono::duration<double>>(period).count());

    if (!watchdog_thread_)
        watchdog_thread_ = std::make_unique<std::thread>(&RobotDriver::_watchdog_thread_function, this);

}

/**
 * @brief RobotDriver::watchdog_trigger updates the trigger signal.
 * @param trigger The time_point
 * @param status. The desired status. If false, the driver is going to stop.
 */
void RobotDriver::watchdog_trigger(const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>& trigger,
                                   const bool &status)
{
    std::scoped_lock lock(mutex_watchdog_);
    last_trigger_    = trigger;
    watchdog_status_ = status;
}


}
