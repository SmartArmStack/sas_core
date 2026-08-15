# Python wrapper module via pybind11

find_package(Python3 REQUIRED COMPONENTS Development)

# pybind11 import block [BEGIN]
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvv #
set(PYBIND11_FINDPYTHON ON) # Fix CMP0148 Warning. https://github.com/pybind/pybind11/issues/4785
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../pybind11)
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^ #
# pybind11 import block [END] #

pybind11_add_module(_${PROJECT_NAME} SHARED
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_core_py.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_robot_driver_py.cpp
)

target_include_directories(_${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>)

target_compile_definitions(_${PROJECT_NAME} PRIVATE IS_SAS_PYTHON_BUILD)
target_link_libraries(_${PROJECT_NAME} PRIVATE sas_core_pure -ldqrobotics)

# Install path: use _SAS_PYTHON_INSTALL_DIR if set by parent (ROS2/ament),
# otherwise default to the standard Python site-packages location.
if(DEFINED _SAS_PYTHON_INSTALL_DIR)
  set(_SAS_PY_INSTALL_DEST "${_SAS_PYTHON_INSTALL_DIR}")
else()
  set(_SAS_PY_INSTALL_DEST "lib/python3/dist-packages/${PROJECT_NAME}")
endif()

install(TARGETS _${PROJECT_NAME}
  DESTINATION "${_SAS_PY_INSTALL_DEST}")