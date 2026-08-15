"""Test that sas_core Python bindings can be imported from a downstream ROS2 package."""

def test_python_imports():
    """Verify sas_core Python module is importable and usable."""
    from sas_core import Clock, Statistics, RobotDriver, ShutdownSignaler

    # Verify Clock can be instantiated (requires sampling_time argument)
    clock = Clock(0.1)
    assert isinstance(clock, Clock), "Clock(0.1) should return a Clock instance"

    # Verify Statistics, RobotDriver, ShutdownSignaler are importable
    assert Statistics is not None
    assert RobotDriver is not None
    assert ShutdownSignaler is not None

    print("All sas_core Python imports successful from test_consumer!")
    return True


if __name__ == "__main__":
    test_python_imports()