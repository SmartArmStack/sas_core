# sas_core

> [!TIP]
> Repository for this module: https://github.com/SmartArmStack/sas_core. <br/>
> More information about SmartArmStack is available in https://smartarmstack.github.io/.

## Contents

- `include/sas_core/` — public C++ headers.
- `src/` — implementation of the shared library and pybind11 bindings.
- `scripts/` — example Python scripts.
- `src/examples/` — C++ example programs and test nodes.

## Examples

Testing on a docker container.

```bash
docker run --rm murilomarinho/sas:jazzy bash -c "ros2 run sas_core sas_clock_example"
```

```bash
ros2 run sas_core sas_core_example
ros2 run sas_core sas_clock_example
ros2 run sas_core sas_clock_sched_fifo_example
ros2 run sas_core sas_robot_driver_example
```

```bash
ros2 run sas_core sas_clock_example_py.py
ros2 run sas_core sas_robot_driver_subclass_example_py.py
ros2 run sas_core sas_clock_sched_fifo_example_py.py
```

The `scripts/sas_robot_driver_subclass_example_py.py` file demonstrates how to
subclass `sas_core.RobotDriver` in Python and contains a minimal working
example.
