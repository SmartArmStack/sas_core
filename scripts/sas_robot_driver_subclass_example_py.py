#!/bin/python3
# Copyright (c) 2016-2026 Murilo Marques Marinho
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
# ################################################################

"""
@file sas_robot_driver_subclass_example_py.py
@brief Example subclass of sas_core.RobotDriver in Python.

This module provides a minimal example showing how to subclass the
`sas_core.RobotDriver` Python binding and implement the required methods.
It is intended for documentation and testing purposes only.
"""

import numpy as np
from sas_core import RobotDriver, ShutdownSignaler

class ExampleRobotDriver(RobotDriver):
    """
    @class ExampleRobotDriver
    @brief Example RobotDriver subclass.

    Minimal example showing the typical methods required by a RobotDriver
    implementation.
    """
    break_loop = False

    def __init__(self, ss: ShutdownSignaler):
        """
        @brief Constructor.
        @param ss ShutdownSignaler instance used by the base RobotDriver to
                  coordinate shutdown requests.
        """
        RobotDriver.__init__(self, ss)
        print("ExampleRobotDriver::__init__")
        self.joint_positions = None

    def connect(self):
        """
        @brief Establish connection to the robot/hardware.
        @return None
        """
        print("ExampleRobotDriver::connect")

    def disconnect(self):
        """
        @brief Terminate connection to the robot/hardware.
        @return None
        """
        print("ExampleRobotDriver::disconnect")

    def initialize(self):
        """
        @brief Initialize the robot driver (bring hardware to an operational state).
        @return None
        """
        print("ExampleRobotDriver::initialize")

    def deinitialize(self):
        """
        @brief Deinitialize the robot driver (clean up resources).
        @return None
        """
        print("ExampleRobotDriver::deinitialize")

    def get_joint_positions(self):
        """
        @brief Get the current joint positions.
        @return numpy.ndarray or None Current joint positions in radians, or None if unknown.
        """
        return self.joint_positions

    def set_target_joint_positions(self, target_joint_positions_rad):
        """
        @brief Set the desired joint positions (target).
        @param target_joint_positions_rad numpy.ndarray Target joint positions in radians.
        @return None
        """
        self.joint_positions = target_joint_positions_rad

def main():
    """Example main demonstrating `ExampleRobotDriver`.

    - Creates a `ShutdownSignaler`.
    - Instantiates and uses `ExampleRobotDriver`: connect(), initialize(),
      set target positions, set joint limits, deinitialize(), disconnect().

    No parameters. Returns None.
    """

    ss = ShutdownSignaler()

    robot = ExampleRobotDriver(ss)
    robot.connect()
    robot.initialize()
    robot.set_target_joint_positions(np.array([0.0,1.0,2.0,3.0,4.0,5.0,6.0]))
    print(robot.get_joint_positions())
    robot.set_joint_limits((
        np.array([-5.0, -5.0, -5.0, -5.0, -5.0]),
        np.array([5.0, 5.0, 5.0, 5.0, 5.0]),
    ))
    print(robot.get_joint_limits())
    robot.deinitialize()
    robot.disconnect()

if __name__ == '__main__':
    main()