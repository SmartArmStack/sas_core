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
 * @file sas_robot_driver_example_main.cpp
 * @brief C++ example showcasing a sample RobotDriver subclass.
 */
#include <sas_core/examples/sas_robot_driver_example.hpp>
#include <iostream>

#include<signal.h>
static std::atomic_bool kill_this_process(false);
void sig_int_handler(int)
{
    kill_this_process = true;
}

int main(int,char**)
{
    if(signal(SIGINT, sig_int_handler) == SIG_ERR)
    {
        throw std::runtime_error("sas_robot_driver_example_main::Error setting the signal int handler.");
    }

    auto configuration = sas::RobotDriverExampleConfiguration();
    configuration.name = "Example_Robot_123";
    configuration.initial_joint_positions = VectorXd::Random(7);

    auto robot_driver_example = sas::RobotDriverExample(configuration,&kill_this_process);

    robot_driver_example.connect();
    robot_driver_example.initialize();

    std::cout << "Initial joint positions: " << robot_driver_example.get_joint_positions().transpose() << std::endl;

    VectorXd target_joint_positions = VectorXd::Random(7);
    std::cout << "Target joint positions: " << target_joint_positions.transpose() << std::endl;

    robot_driver_example.set_target_joint_positions(target_joint_positions);
    std::cout << "Joint positions after change: " << robot_driver_example.get_joint_positions().transpose() << std::endl;

    assert((target_joint_positions == robot_driver_example.get_joint_positions()));

    robot_driver_example.deinitialize();
    robot_driver_example.disconnect();

    return 0;
}
