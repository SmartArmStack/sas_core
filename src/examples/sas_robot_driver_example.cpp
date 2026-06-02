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

/**
 * @file sas_robot_driver_example.cpp
 * @brief Example implementation of a RobotDriver.
 */
#include <sas_core/examples/sas_robot_driver_example.hpp>
#include <iostream>

sas::RobotDriverExample::RobotDriverExample(const RobotDriverExampleConfiguration &configuration, std::atomic_bool *break_loops):
    RobotDriver(break_loops),
    configuration_(configuration)
{
    set_joint_limits(configuration.joint_limits);
}

VectorXd sas::RobotDriverExample::get_joint_positions()
{
    return joint_positions_;
}

void sas::RobotDriverExample::set_target_joint_positions(const VectorXd &set_target_joint_positions_rad)
{
    if(joint_positions_.size() != set_target_joint_positions_rad.size())
        throw std::runtime_error("sas::RobotDriverExample::set_target_joint_positions invalid size for set_target_joint_positions_rad");
    joint_positions_ = set_target_joint_positions_rad;
}

void sas::RobotDriverExample::connect()
{
    std::cout << "Connecting to " << configuration_.name << std::endl;
}

void sas::RobotDriverExample::disconnect()
{
    std::cout << "Disconnecting from " << configuration_.name << std::endl;
}

void sas::RobotDriverExample::initialize()
{
    std::cout << "Initializing " << configuration_.name << std::endl;
    joint_positions_ = configuration_.initial_joint_positions;
}

void sas::RobotDriverExample::deinitialize()
{
    std::cout << "Deinitializing " << configuration_.name << std::endl;
}
