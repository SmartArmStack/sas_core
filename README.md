# sas_core (thin wrapper)

> [!TIP]
> Repository for this module: https://github.com/SmartArmStack/sas_core. <br/>
> More information about SmartArmStack is available in https://smartarmstack.github.io/.

`sas_core` is a **thin ROS 2 wrapper** around the SmartArmStack core. It
contains no C++ implementation and no Python extension module of its own; it
forwards to the two packages that provide the core:

| Piece | Provided by | Installed as |
|---|---|---|
| C++ library (`libmarinholab_sas_core`) + headers + CMake config | [MarinhoLab/sas_cpp](https://github.com/MarinhoLab/sas_cpp) | `libmarinholab-sas-core` `.deb` (target namespace `marinholab::sas::core`) |
| Python bindings | [MarinhoLab/sas_py](https://github.com/MarinhoLab/sas_py) | `marinholab-sas-core` on PyPI (import `marinholab.sas.core`) |

On Ubuntu the `.deb` links the dynamic `libdqrobotics` from the
[dqrobotics PPA](https://launchpad.net/~dqrobotics-dev/+archive/ubuntu/development);
in the provided docker environment both are already installed.

## What this package provides

- **C++**: the ament target `sas_core` (`ament_target_dependencies(<pkg> sas_core ...)`)
  forwarding to `marinholab::sas::core`, plus **compatibility headers**
  `include/sas_core/*.hpp` that keep the legacy include paths
  (`#include <sas_core/sas_clock.hpp>`) and the legacy `namespace sas` working
  via `#include <marinholab/sas/core/...>` + a namespace alias.
- **Python**: a pure-Python `sas_core` shim that re-exports
  `Clock`, `Statistics`, `RobotDriver`, `ShutdownSignaler` from
  `marinholab.sas.core`, so `from sas_core import Clock` keeps working.

## Contents

- `include/sas_core/` — compatibility C++ headers (one-line forwards).
- `sas_core/__init__.py` — Python compatibility shim.
- `scripts/` — example Python scripts + `sas_core_smoke_test.py`.
- `docker/` — build environment and integration smoke test.

## Installation

```bash
# C++ core (until the .deb is published to an apt repository, build it from source):
sudo add-apt-repository ppa:dqrobotics-dev/development
sudo apt-get update
sudo apt-get install -y libdqrobotics
#   then build sas_cpp with dpkg-buildpackage and dpkg -i the result,
#   or simply: sudo apt-get install libmarinholab-sas-core  (once published)

# Python bindings:
python3 -m pip install marinholab-sas-core

# This wrapper (inside a ROS 2 workspace):
colcon build
```

## Examples

The C++ example programs live with the C++ core
([MarinhoLab/sas_cpp](https://github.com/MarinhoLab/sas_cpp), built with
`-DMARINHO_LAB_SAS_CORE_BUILD_EXAMPLES=ON`). The Python examples in
`scripts/` run against the PyPI-installed bindings:

```bash
ros2 run sas_core sas_clock_example_py.py
ros2 run sas_core sas_clock_sched_fifo_example_py.py
ros2 run sas_core sas_robot_driver_subclass_example_py.py
```

`sas_robot_driver_subclass_example_py.py` demonstrates subclassing
`sas_core.RobotDriver` in Python.

## Testing

The docker environment builds the wrapper with `colcon` and runs a smoke test
covering both consumption paths (Python shim + C++ compatibility headers
against the installed library):

```bash
cd docker
docker compose build
docker compose up
```
