#pragma once
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
# ################################################################
# Contributors:
#
#   1. Juan Jose Quiroz Omana (juanjose.quirozomana@manchester.ac.uk)
#      Added the Watchdog functionaly initially proposed in
#      https://github.com/SmartArmStack/sas_core/pull/1
*/

#include <atomic>
#include <mutex>
#include <thread>
#include <memory>
#include <chrono>
#include <sas_core/sas_clock.hpp>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

namespace sas
{
class RobotDriver
{
protected:
    std::atomic_bool* break_loops_;
    std::tuple<VectorXd, VectorXd> joint_limits_;
    VectorXd joint_velocities_;
    VectorXd joint_torques_;

    std::unique_ptr<sas::Clock> clock_;
    std::unique_ptr<std::thread> watchdog_thread_;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> time_point_from_the_client_;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> time_point_from_the_server_;
    bool watchdog_status_;
    void _watchdog_thread_function();
    std::mutex mutex_watchdog_;
    double max_acceptable_delay_ = 0.1;
    double watchdog_period_;

    RobotDriver(std::atomic_bool* break_loops);

    RobotDriver()=delete;
    RobotDriver(const RobotDriver&)=delete;
public:
    enum class Functionality{
        None=0,
        PositionControl,
        VelocityControl,
        ForceControl,
        Homing,
        ClearPositions,
        Watchdog
    };

    virtual VectorXd get_joint_positions() = 0;
    virtual void set_target_joint_positions(const VectorXd& set_target_joint_positions_rad) = 0;

    virtual VectorXd get_joint_velocities();
    virtual void set_target_joint_velocities(const VectorXd& set_target_joint_velocities);

    virtual VectorXd get_joint_torques();
    virtual void set_target_joint_torques(const VectorXd& set_target_joint_torques);

    virtual std::tuple<VectorXd, VectorXd> get_joint_limits();
    virtual void set_joint_limits(const std::tuple<VectorXd, VectorXd>& joint_limits);

    void watchdog_start(const std::chrono::nanoseconds& period);
    void watchdog_trigger(const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>& time_point_from_the_client,
                          const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>& time_point_from_the_server,
                          const bool& status);
    void watchdog_set_maximum_acceptable_delay(const double& max_acceptable_delay);


    virtual void connect()=0;
    virtual void disconnect()=0;

    virtual void initialize()=0;
    virtual void deinitialize()=0;
};
}



