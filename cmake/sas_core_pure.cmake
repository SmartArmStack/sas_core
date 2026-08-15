# sas_core_pure: the pure C++ library (no ROS2/ament dependencies)

find_package(Eigen3 REQUIRED)

# Use CURRENT_LIST_DIR so paths resolve relative to this cmake file
set(_sas_core_pure_dir "${CMAKE_CURRENT_LIST_DIR}/../src")

set(_sas_core_pure_sources
    ${_sas_core_pure_dir}/sas_clock.cpp
    ${_sas_core_pure_dir}/sas_core.cpp
    ${_sas_core_pure_dir}/sas_object.cpp
    ${_sas_core_pure_dir}/sas_shutdown_signaler.cpp
    ${_sas_core_pure_dir}/sas_robot_driver.cpp
    ${_sas_core_pure_dir}/examples/sas_robot_driver_example.cpp
    ${_sas_core_pure_dir}/eigen3_std_conversions.cpp
)

add_library(sas_core_pure STATIC ${_sas_core_pure_sources})

set_target_properties(sas_core_pure PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(sas_core_pure
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sas_core_pure
    PUBLIC
    -ldqrobotics
    Eigen3::Eigen
)

unset(_sas_core_pure_dir)
unset(_sas_core_pure_sources)