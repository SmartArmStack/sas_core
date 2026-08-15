cmake_minimum_required(VERSION 3.11)
project(sas_core)

option(ROS2_BUILD "Enable ROS2/ament build (examples + ament integration)" ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Core libraries (always built) ----
include(cmake/cpplib.cmake)

if(ROS2_BUILD)
    find_package(ament_cmake REQUIRED)
    ament_python_install_package(${PROJECT_NAME})
    set(_SAS_PYTHON_INSTALL_DIR "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}")
endif()

include(cmake/pythonlib.cmake)

# ---- ROS2 / ament integration (conditional) ----
if(ROS2_BUILD)
    # INTERFACE alias for downstream ROS packages
    add_library(sas_core INTERFACE)
    target_link_libraries(sas_core INTERFACE sas_core_pure)

    ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
    ament_export_dependencies(Eigen3)

    install(DIRECTORY include/ DESTINATION include)

    install(TARGETS sas_core sas_core_pure
        EXPORT export_${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
    )

    # Example executables
    foreach(_name IN ITEMS sas_core_example sas_clock_example
        sas_clock_sched_fifo_example)
        add_executable(${_name} src/examples/${_name}.cpp)
        target_link_libraries(${_name} sas_core_pure)
        if(_name STREQUAL "sas_core_example")
            target_link_libraries(${_name} -ldqrobotics)
        endif()
        install(TARGETS ${_name} DESTINATION lib/${PROJECT_NAME})
    endforeach()

    add_executable(sas_robot_driver_example
        src/examples/sas_robot_driver_example_main.cpp)
    target_link_libraries(sas_robot_driver_example sas_core_pure)
    install(TARGETS sas_robot_driver_example DESTINATION lib/${PROJECT_NAME})

    install(DIRECTORY
        scripts/
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        DESTINATION lib/${PROJECT_NAME}
    )

    ament_package()
endif()
