#!/usr/bin/env python3
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

"""Smoke test for the sas_core thin wrapper.

Verifies both consumption paths used by downstream packages:

- Python: ``from sas_core import ...`` resolves through the compatibility
  shim to the ``marinholab.sas.core`` extension installed from PyPI, and a
  Clock actually runs.
- C++: the CMake package config installed by the libmarinholab-sas-core .deb
  is locatable (covers ``find_package(marinholab_sas_core)``, which also
  resolves Eigen3 and recreates dqrobotics::dqrobotics).

Exits non-zero on any failure.
"""

import os
import subprocess
import sys
import tempfile


def check_python_bindings():
    from sas_core import Clock, Statistics, RobotDriver, ShutdownSignaler
    import marinholab.sas.core as real

    # The shim must expose the exact same classes as the PyPI package.
    assert Clock is real.Clock, "Clock shim mismatch"
    assert Statistics is real.Statistics, "Statistics shim mismatch"
    assert RobotDriver is real.RobotDriver, "RobotDriver shim mismatch"
    assert ShutdownSignaler is real.ShutdownSignaler, "ShutdownSignaler mismatch"

    # Exercise a real Clock briefly.
    clock = Clock(0.01)
    clock.init()
    clock.update_and_sleep()
    elapsed = clock.get_elapsed_time_sec()
    assert elapsed >= 0.0, f"unexpected elapsed time {elapsed}"
    assert isinstance(clock.get_time(Clock.TimeType.Computational), float)
    assert isinstance(
        clock.get_statistics(Statistics.Mean, Clock.TimeType.Computational),
        float,
    )
    print(f"[python] sas_core shim OK (Clock elapsed {elapsed:.4f}s)")


def check_cmake_package():
    # Faithful consumer probe: configure+build+run a minimal CMake *project*
    # (project mode, like colcon) against the installed .deb package. The
    # .deb's config runs find_dependency(Eigen3) and recreates
    # dqrobotics::dqrobotics, so this covers the full downstream path.
    src = (
        "#include <marinholab/sas/core/sas_clock.hpp>\n"
        "#include <iostream>\n"
        "int main() {\n"
        "    marinholab::sas::core::Clock c(0.01);\n"
        "    c.init();\n"
        "    c.update_and_sleep();\n"
        '    std::cout << "probe ok " << c.get_elapsed_time_sec() << std::endl;\n'
        "    return 0;\n"
        "}\n"
    )
    cmake = (
        "cmake_minimum_required(VERSION 3.16)\n"
        "project(probe CXX)\n"
        "find_package(marinholab_sas_core REQUIRED)\n"
        "add_executable(probe main.cpp)\n"
        "target_link_libraries(probe marinholab::sas::core)\n"
    )
    with tempfile.TemporaryDirectory(prefix="sas_core_probe_") as tmp:
        with open(os.path.join(tmp, "main.cpp"), "w") as fh:
            fh.write(src)
        with open(os.path.join(tmp, "CMakeLists.txt"), "w") as fh:
            fh.write(cmake)
        build_dir = os.path.join(tmp, "build")
        cfg = subprocess.run(
            ["cmake", "-S", tmp, "-B", build_dir],
            capture_output=True,
            text=True,
        )
        if cfg.returncode != 0:
            raise RuntimeError(
                "find_package(marinholab_sas_core) configure failed:\n"
                + cfg.stdout
                + cfg.stderr
            )
        build = subprocess.run(
            ["cmake", "--build", build_dir],
            capture_output=True,
            text=True,
        )
        if build.returncode != 0:
            raise RuntimeError(
                "probe build (link against libmarinholab_sas_core) failed:\n"
                + build.stdout
                + build.stderr
            )
        run = subprocess.run(
            [os.path.join(build_dir, "probe")],
            capture_output=True,
            text=True,
        )
        if run.returncode != 0:
            raise RuntimeError(
                "probe run failed:\n" + run.stdout + run.stderr
            )
    print("[cmake] consumer probe OK (find_package + link + run)")


def main() -> int:
    try:
        check_python_bindings()
        check_cmake_package()
    except Exception as exc:  # noqa: BLE001
        print(f"[FAIL] {exc}", file=sys.stderr)
        return 1
    print("[OK] sas_core thin wrapper smoke test passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
