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

import numpy as np
from sas_core import RobotDriver, ShutdownSignaler

class ExampleRobotDriver(RobotDriver):
    break_loop = False

    def __init__(self, ss: ShutdownSignaler):
        RobotDriver.__init__(self, ss)
        print("ExampleRobotDriver::__init__")
        self.joint_positions = None

    def connect(self):
        print("ExampleRobotDriver::connect")

    def disconnect(self):
        print("ExampleRobotDriver::disconnect")

    def initialize(self):
        print("ExampleRobotDriver::initialize")

    def deinitialize(self):
        print("ExampleRobotDriver::deinitialize")

    def get_joint_positions(self):
        return self.joint_positions

    def set_target_joint_positions(self, target_joint_positions_rad):
        self.joint_positions = target_joint_positions_rad

def main():
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