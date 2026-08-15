cmake_minimum_required(VERSION 3.8)
project(standalone_consumer)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Eigen3 REQUIRED)

# Path to the sas_core source tree — required to include cmake modules
set(SAS_CORE_SOURCE_DIR "/root/sas_core_devel/src/sas_core" CACHE PATH "Path to sas_core source")

# Include sas_core pure C++ and Python library definitions (no ROS2/ament needed)
include(${SAS_CORE_SOURCE_DIR}/cmake/cpplib.cmake)
include(${SAS_CORE_SOURCE_DIR}/cmake/pythonlib.cmake)

##############################
# Standalone C++ consumer     #
##############################
add_executable(standalone_consumer src/standalone_consumer.cpp)
target_link_libraries(standalone_consumer sas_core_pure)

##############################
# Standalone Python test      #
##############################
# The Python test runs as a CTest; it requires the built _sas_core module.
find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_test(
    NAME test_python_import
    COMMAND ${Python3_EXECUTABLE} test/test_python_import.py
)
set_tests_properties(test_python_import PROPERTIES
    ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}:${CMAKE_SOURCE_DIR}/.."
)