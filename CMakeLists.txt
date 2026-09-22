cmake_minimum_required(VERSION 3.16)
project(sas_core)

# =============================================================================
# sas_core is a THIN WRAPPER around the SmartArmStack core:
#
#   - C++ library: libmarinholab_sas_core, provided by the
#     libmarinholab-sas-core .deb (source: https://github.com/MarinhoLab/sas_cpp).
#     The .deb installs headers under include/marinholab/sas/core/, the shared
#     library, and the CMake package config (find_package(marinholab_sas_core)).
#   - Python bindings: the PyPI package marinholab-sas-core
#     (https://github.com/MarinhoLab/sas_py), imported as marinholab.sas.core.
#
# This package adds no implementation; it only:
#   1. re-exports the ament target `sas_core` so downstream ROS packages keep
#      working with `ament_target_dependencies(<pkg> sas_core ...)`;
#   2. installs compatibility headers include/sas_core/*.hpp that forward to
#      the .deb's include/marinholab/sas/core/*.hpp and re-alias `namespace sas`;
#   3. installs the pure-Python `sas_core` shim (re-exporting
#      marinholab.sas.core) so `from sas_core import Clock` keeps working.
# =============================================================================

find_package(marinholab_sas_core REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

# Eigen3 is a PUBLIC dependency of the core (its headers include <Eigen/Dense>);
# declare it so downstream ament packages can resolve it through this package.
find_package(Eigen3 REQUIRED)

# ---- ament target ---------------------------------------------------------
# INTERFACE alias forwarding downstream packages to the core target installed
# by the libmarinholab-sas-core .deb.
add_library(sas_core INTERFACE)
# Expose the compatibility headers (include/sas_core/*.hpp) through the
# target's interface so downstream packages that link sas_core::sas_core
# can #include <sas_core/...> in both workspace and installed use.
target_include_directories(sas_core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(sas_core INTERFACE marinholab::sas::core Eigen3::Eigen)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
# Eigen3 and marinholab_sas_core are consumed transitively by downstream
# packages that link the `sas_core` target; propagate them so their
# find_package() calls run in the consumer.
ament_export_dependencies(Eigen3 marinholab_sas_core)

# ---- Compatibility headers ------------------------------------------------
# include/sas_core/*.hpp are thin shims forwarding to the .deb's
# include/marinholab/sas/core/*.hpp and re-aliasing `namespace sas`.
install(DIRECTORY include/ DESTINATION include)

install(TARGETS sas_core
    EXPORT export_${PROJECT_NAME}
)

# ---- Python compatibility shim ---------------------------------------------
# Pure-Python module re-exporting marinholab.sas.core (installed from PyPI by
# the docker environment / user). See sas_core/__init__.py.
ament_python_install_package(${PROJECT_NAME})

# Example scripts (run against the PyPI-installed bindings).
install(
    DIRECTORY scripts/
    FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
