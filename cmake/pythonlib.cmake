# Python wrapper module via pybind11
find_package(Python3 REQUIRED COMPONENTS Development)

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

pybind11_add_module(_sas_core SHARED
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_core_py.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sas_robot_driver_py.cpp
)

target_include_directories(_sas_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(_sas_core PRIVATE IS_SAS_PYTHON_BUILD)
target_link_libraries(_sas_core PRIVATE sas_core_pure -ldqrobotics)

# Install path: ament PYTHON_INSTALL_DIR if available, else site-packages
if(DEFINED _SAS_PYTHON_INSTALL_DIR)
  set(_SAS_PY_DEST "${_SAS_PYTHON_INSTALL_DIR}")
else()
  set(_SAS_PY_DEST "lib/python3/dist-packages/sas_core")
endif()

install(TARGETS _sas_core DESTINATION "${_SAS_PY_DEST}")