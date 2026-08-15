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

ament_package()