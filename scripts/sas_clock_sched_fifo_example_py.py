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
import os
from sas_core import Clock, Statistics

if __name__=='__main__':

    # 1 ms clock
    clock = Clock(0.001)

    param = os.sched_param(os.sched_get_priority_max(os.SCHED_FIFO))
    os.sched_setscheduler(0, os.SCHED_FIFO, param)

    # Always initialize before the loop to reduce latency
    clock.init()

    for i in range(0,50):
        # Starting the loop with an update reduces issues with the first loop taking too long
        clock.update_and_sleep()

    # Statistics
    print("Statistics for the entire loop")
    print("  Mean computation time: {}".format(clock.get_statistics(
        Statistics.Mean, Clock.TimeType.Computational)
    ))
    print("  Mean idle time: {}".format(clock.get_statistics(
        Statistics.Mean, Clock.TimeType.Idle)
    ))
    print("  Mean effective thread sampling time: {}".format(clock.get_statistics(
        Statistics.Mean, Clock.TimeType.EffectiveSampling)
    ))
    print("  Overrun count: ".format(clock.get_overrun_count()))
