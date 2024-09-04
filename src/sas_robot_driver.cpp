/*
# Copyright (c) 2016-2020 Murilo Marques Marinho
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
# ################################################################*/
#include <sas_core/sas_robot_driver.hpp>

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

}
