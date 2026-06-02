"""
@file __init__.py
@brief Package entry for the sas_core Python bindings.

This module re-exports the primary Python bindings provided by the
compiled extension module :mod:`sas_core._sas_core`.

- Clock: high-resolution timing and sleep helpers.
- Statistics: enumeration for statistical types.
- RobotDriver: abstract robot driver interface that can be inherited by Python classes.
- ShutdownSignaler: request and wait for orderly shutdown.

The concrete implementations live in the compiled extension module
``sas_core._sas_core``.

"""

from sas_core._sas_core import Clock, Statistics, RobotDriver, ShutdownSignaler

__all__ = ["Clock", "Statistics", "RobotDriver", "ShutdownSignaler"]
