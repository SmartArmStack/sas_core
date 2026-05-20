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
from sas_core import RobotDriver

class ExampleRobotDriver(RobotDriver):
    break_loop = False

    def __init__(self):
        RobotDriver.__init__(self, ExampleRobotDriver.break_loop)
        pass

    def connect(self):
        pass

    def disconnect(self):
        pass

    def initialize(self):
        pass

    def deinitialize(self):
        pass

    def get_joint_positions(self):
        pass

    def set_target_joint_positions(self, set_target_joint_positions_rad):
        pass

def main():
    robot = ExampleRobotDriver()
    robot.connect()
    robot.initialize()
    robot.set_target_joint_positions(np.array([0.0,1.0,2.0,3.0,4.0,5.0,6.0]))
    robot.get_joint_positions()
    robot.deinitialize()
    robot.disconnect()

if __name__ == '__main__':
    main()