cmake_minimum_required(VERSION 3.8)
project(test_consumer)

find_package(ament_cmake REQUIRED)
find_package(sas_core REQUIRED)

# Build a simple executable that links against the sas_core library
add_executable(test_consumer src/test_consumer.cpp)
target_link_libraries(test_consumer sas_core::sas_core_pure)

install(TARGETS
    test_consumer
    DESTINATION lib/${PROJECT_NAME})

# Python import test
find_package(Python3 REQUIRED COMPONENTS Interpreter)
if(Python3_FOUND)
    add_test(
        NAME test_python_import
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/test_python_import.py
    )
    set_tests_properties(test_python_import PROPERTIES
        ENVIRONMENT "PYTHONPATH=${CMAKE_INSTALL_PREFIX}/lib/python3.12/site-packages:${CMAKE_INSTALL_PREFIX}/sas_core/lib/python3.12/site-packages"
    )
endif()

ament_package()