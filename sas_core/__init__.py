# Copyright (c) 2012-2026 Murilo Marques Marinho
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

"""
@file __init__.py
@brief Package entry for the sas_core Python bindings (compatibility shim).

The Python bindings now live in the PyPI package ``marinholab-sas-core``
(https://github.com/MarinhoLab/sas_py), imported as ``marinholab.sas.core``.
This module re-exports its public names so existing code keeps working:

    from sas_core import Clock, Statistics, RobotDriver, ShutdownSignaler

``sas_core`` no longer ships its own compiled extension module; it is a thin
wrapper around the PyPI package. Install the bindings with:

    pip install marinholab-sas-core
"""

from marinholab.sas.core import (
    Clock,
    RobotDriver,
    ShutdownSignaler,
    Statistics,
)

__all__ = ["Clock", "Statistics", "RobotDriver", "ShutdownSignaler"]
