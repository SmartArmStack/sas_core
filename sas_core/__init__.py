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
    Statistics,
    RobotDriver,
    ShutdownSignaler,
)

__all__ = ["Clock", "Statistics", "RobotDriver", "ShutdownSignaler"]
