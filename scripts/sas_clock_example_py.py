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
# ################################################################

from sas_core import Clock, Statistics

if __name__=='__main__':

    # 10 ms clock
    clock = Clock(0.01)

    # Always initialize before the loop to reduce latency
    clock.init()

    for i in range(0,50):
        # Starting the loop with an update reduces issues with the first loop taking too long
        clock.update_and_sleep()
        print("Loop n = {}".format(i))
        print("  Elapsed time: {}".format(clock.get_elapsed_time_sec()))
        print("  Latest computation time: {}".format(clock.get_time(Clock.TimeType.Computational)))
        print("  Latest idle time: {}".format(clock.get_time(Clock.TimeType.Idle)))
        print("  Latest effective thread sampling time: {}".format(
            clock.get_time(clock.TimeType.EffectiveSampling)
        ))
        print("  Desired thread sampling time: {}".format(
            clock.get_desired_thread_sampling_time_sec()
        ))
        print("  Overrun count: ".format(clock.get_overrun_count()))

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
