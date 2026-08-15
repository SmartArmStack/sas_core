cmake_minimum_required(VERSION 3.8)
project(sas_core)

option(ROS2_BUILD "Enable ROS2/ament build (examples + ament integration)" ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find non-ROS dependencies
find_package(Eigen3 REQUIRED)

##############################
# Pure C++ library            #
##############################
include(cmake/cpplib.cmake)

##############################
# Python wrapper (pybind11)   #
##############################
if(ROS2_BUILD)
    find_package(ament_cmake REQUIRED)
    ament_python_install_package(${PROJECT_NAME})
    # ament_python_install_package sets PYTHON_INSTALL_DIR — pass it to pythonlib.cmake
    set(_SAS_PYTHON_INSTALL_DIR "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}")
endif()
include(cmake/pythonlib.cmake)

##############################
# ROS2 / ament integration    #
##############################
if(ROS2_BUILD)
    # INTERFACE alias so external ROS packages can link against `sas_core`.
    add_library(sas_core INTERFACE)
    target_link_libraries(sas_core INTERFACE sas_core_pure)
    target_include_directories(sas_core INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

    ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
    ament_export_dependencies(Eigen3)
    ament_export_include_directories(include)

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

    ################################################################################
    # Example executables
    ################################################################################
    add_executable(sas_core_example src/examples/sas_core_example.cpp)
    target_link_libraries(sas_core_example -ldqrobotics sas_core_pure)
    install(TARGETS sas_core_example DESTINATION lib/${PROJECT_NAME})

    add_executable(sas_clock_example src/examples/sas_clock_example.cpp)
    target_link_libraries(sas_clock_example sas_core_pure)
    install(TARGETS sas_clock_example DESTINATION lib/${PROJECT_NAME})

    add_executable(sas_clock_sched_fifo_example src/examples/sas_clock_sched_fifo_example.cpp)
    target_link_libraries(sas_clock_sched_fifo_example sas_core_pure)
    install(TARGETS sas_clock_sched_fifo_example DESTINATION lib/${PROJECT_NAME})

    add_executable(sas_robot_driver_example src/examples/sas_robot_driver_example_main.cpp)
    target_link_libraries(sas_robot_driver_example sas_core_pure)
    install(TARGETS sas_robot_driver_example DESTINATION lib/${PROJECT_NAME})

    ################################################################################
    # Python executables
    ################################################################################
    install(PROGRAMS
        scripts/sas_clock_example_py.py
        scripts/sas_robot_driver_subclass_example_py.py
        scripts/sas_clock_sched_fifo_example_py.py
        DESTINATION lib/${PROJECT_NAME}
    )

    ament_package()
endif()
