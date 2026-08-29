# Build the pure C++ library (no ROS2/ament dependencies)
find_package(Eigen3 REQUIRED)

add_library(sas_core_pure STATIC)
target_sources(sas_core_pure PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_clock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_shutdown_signaler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_robot_driver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/examples/sas_robot_driver_example.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/eigen3_std_conversions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_thread_manager.cpp
)

set_target_properties(sas_core_pure PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(sas_core_pure PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sas_core_pure PUBLIC -ldqrobotics Eigen3::Eigen)