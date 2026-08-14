# sas_core_pure: the pure C++ library (no ROS2/ament dependencies)

find_package(Eigen3 REQUIRED)

add_library(sas_core_pure STATIC
    sas_clock.cpp
    sas_core.cpp
    sas_object.cpp
    sas_shutdown_signaler.cpp
    sas_robot_driver.cpp
    examples/sas_robot_driver_example.cpp
    eigen3_std_conversions.cpp
)

set_target_properties(sas_core_pure PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(sas_core_pure
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sas_core_pure
    PUBLIC
    -ldqrobotics
    Eigen3::Eigen
)