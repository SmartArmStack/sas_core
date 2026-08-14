cmake_minimum_required(VERSION 3.8)
project(sas_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#################################
# pybind11 import block [BEGIN] #
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvv #
set(PYBIND11_FINDPYTHON ON) # Fix CMP0148 Warning. https://github.com/pybind/pybind11/issues/4785
add_subdirectory(pybind11)
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^ #
# pybind11 import block [END] #
###############################

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(Eigen3 REQUIRED)

##############################
# Pure C++ library (src/)     #
##############################
add_subdirectory(src)

# INTERFACE alias so external ROS packages can still link against `sas_core`.
# All symbols come from sas_core_pure transitively.
add_library(sas_core INTERFACE)
target_link_libraries(sas_core INTERFACE sas_core_pure)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(Eigen3)

install(
    DIRECTORY include/
    DESTINATION include
    )

install(
    TARGETS sas_core sas_core_pure
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    )

##############################
# Binaries                    #
##############################
add_executable(sas_core_example
    src/examples/sas_core_example.cpp)

target_link_libraries(sas_core_example
    -ldqrobotics
    sas_core_pure
    )

install(TARGETS
    sas_core_example
    DESTINATION lib/${PROJECT_NAME})

add_executable(sas_clock_example
    src/examples/sas_clock_example.cpp)

target_link_libraries(sas_clock_example
    sas_core_pure
    )

install(TARGETS
    sas_clock_example
    DESTINATION lib/${PROJECT_NAME})

add_executable(sas_clock_sched_fifo_example
    src/examples/sas_clock_sched_fifo_example.cpp)

target_link_libraries(sas_clock_sched_fifo_example
    sas_core_pure
    )

install(TARGETS
    sas_clock_sched_fifo_example
    DESTINATION lib/${PROJECT_NAME})

add_executable(sas_robot_driver_example
    src/examples/sas_robot_driver_example_main.cpp)

target_link_libraries(sas_robot_driver_example
    sas_core_pure
    )

install(TARGETS
    sas_robot_driver_example
    DESTINATION lib/${PROJECT_NAME})

##############################
# Pybind11                    #
##############################
ament_python_install_package(${PROJECT_NAME})

pybind11_add_module(_${PROJECT_NAME} SHARED
    src/sas_core_py.cpp
    src/sas_robot_driver_py.cpp
    )

target_include_directories(_${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_definitions(_${PROJECT_NAME} PRIVATE IS_SAS_PYTHON_BUILD)
target_link_libraries(_${PROJECT_NAME} PRIVATE sas_core_pure -ldqrobotics)

install(TARGETS _${PROJECT_NAME}
  DESTINATION "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}"
)

##############################
# Python executables          #
##############################
install(PROGRAMS
  scripts/sas_clock_example_py.py
  scripts/sas_robot_driver_subclass_example_py.py
  scripts/sas_clock_sched_fifo_example_py.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
