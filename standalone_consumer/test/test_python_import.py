"""Test that sas_core Python bindings can be imported from a standalone (non-ROS2) CMake project."""

def test_python_imports():
    from sas_core import Clock, Statistics, RobotDriver, ShutdownSignaler

    clock = Clock(0.1)
    assert isinstance(clock, Clock)
    assert Statistics is not None
    assert RobotDriver is not None
    assert ShutdownSignaler is not None

    print("All sas_core Python imports successful from standalone_consumer (no ROS2)!")
    return True


if __name__ == "__main__":
    test_python_imports()