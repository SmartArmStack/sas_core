cmake_minimum_required(VERSION 3.8)
project(sas_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(pybind11 REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(Eigen3 REQUIRED)

##### CPP LIBRARY #####

add_library(${PROJECT_NAME} SHARED
    src/sas_clock.cpp
    src/sas_core.cpp
    src/sas_object.cpp
    # sas_robot_driver
    src/sas_robot_driver.cpp
    src/examples/sas_robot_driver_example.cpp
    src/eigen3_std_conversions.cpp
    )

ament_target_dependencies(${PROJECT_NAME} Eigen3)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(Eigen3)

target_link_libraries(${PROJECT_NAME}
    -ldqrobotics
    Eigen3::Eigen
    )

install(
    DIRECTORY include/
    DESTINATION include
    )

install(
    TARGETS ${PROJECT_NAME}
    EXPORT export_${PROJECT_NAME}
    LIBRARY DESTINATION lib
    #ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )

##END## CPP LIBRARY #####

##### CPP BINARY #####

add_executable(sas_core_example
    src/examples/sas_core_example.cpp)

target_link_libraries(sas_core_example
    -ldqrobotics
    ${PROJECT_NAME}
    )

install(TARGETS
    sas_core_example
    DESTINATION lib/${PROJECT_NAME})

##END## CPP BINARY #####

##### CPP BINARY #####

add_executable(sas_clock_example
    src/examples/sas_clock_example.cpp)

target_link_libraries(sas_clock_example
    ${PROJECT_NAME}
    )

install(TARGETS
    sas_clock_example
    DESTINATION lib/${PROJECT_NAME})

##END## CPP BINARY #####

##### CPP BINARY #####

add_executable(sas_robot_driver_example
    src/examples/sas_robot_driver_example_main.cpp)

target_link_libraries(sas_robot_driver_example
    ${PROJECT_NAME}
    )

install(TARGETS
    sas_robot_driver_example
    DESTINATION lib/${PROJECT_NAME})

##END## CPP BINARY #####

##### PYBIND11 LIBRARY #####

ament_python_install_package(${PROJECT_NAME})

pybind11_add_module(_${PROJECT_NAME} SHARED
    src/sas_core_py.cpp
    )

target_include_directories(_${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_definitions(_${PROJECT_NAME} PRIVATE IS_SAS_PYTHON_BUILD)
# https://github.com/pybind/pybind11/issues/387
target_link_libraries(_${PROJECT_NAME} PRIVATE ${PROJECT_NAME} -ldqrobotics)

install(TARGETS _${PROJECT_NAME}
  DESTINATION "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}"
)

##END## PYBIND11 LIBRARY #####


if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    # the following line skips the linter which checks for copyrights
    # comment the line when a copyright and license is added to all source files
    set(ament_cmake_copyright_FOUND TRUE)
    # the following line skips cpplint (only works in a git repo)
    # comment the line when this package is in a git repo and when
    # a copyright and license is added to all source files
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif()

ament_package()
