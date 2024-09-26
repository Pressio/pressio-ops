cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(pressio C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(colors)

#=====================================================================
# versioning
#=====================================================================
# adapted from Eigen
file(READ "${PROJECT_SOURCE_DIR}/include/pressio/ops_macros.hpp" _pressio_ops_macros)
string(REGEX MATCH "define[ \t]+PRESSIO_OPS_MAJOR_VERSION[ \t]+([0-9]+)" _major_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_MAJOR_VERSION "${CMAKE_MATCH_1}")

string(REGEX MATCH "define[ \t]+PRESSIO_OPS_MINOR_VERSION[ \t]+([0-9]+)" _minor_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_MINOR_VERSION "${CMAKE_MATCH_1}")

string(REGEX MATCH "define[ \t]+PRESSIO_OPS_PATCH_VERSION[ \t]+([0-9]+)" _patch_version_match "${_pressio_ops_macros}")
set(PRESSIO_OPS_PATCH_VERSION "${CMAKE_MATCH_1}")

set(PRESSIO_OPS_VERSION_NUMBER ${PRESSIO_OPS_MAJOR_VERSION}.${PRESSIO_OPS_MINOR_VERSION}.${PRESSIO_OPS_PATCH_VERSION})
message("${Magenta}>> version = ${PRESSIO_OPS_VERSION_NUMBER} ${ColourReset}")

#=====================================================================
# c++ standard
#=====================================================================
if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

message("${Magenta}>> CMAKE_CXX_STANDARD is set to ${CMAKE_CXX_STANDARD} ${ColourReset}")

if(CMAKE_CXX_STANDARD STREQUAL "17"
    OR CMAKE_CXX_STANDARD STREQUAL "20")
  if(NOT "cxx_std_${CMAKE_CXX_STANDARD}" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(FATAL_ERROR "Compiler does not support C++${CMAKE_CXX_STANDARD}. This is required.")
  endif()
endif()

################################################################################

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY include/pressio
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_library(pressioops INTERFACE)

target_include_directories(
  pressioops INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
  TARGETS pressioops
  EXPORT pressioopsTargets
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(
  EXPORT pressioopsTargets
  FILE pressioopsTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pressioops)
export(
  TARGETS pressioops
  FILE pressioopsTargets.cmake)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/pressioopsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/pressioopsConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pressioops)

write_basic_package_version_file (pressioopsConfigVersion.cmake
                                  VERSION ${PRESSIO_OPS_VERSION_NUMBER}
                                  COMPATIBILITY SameMajorVersion
				  ARCH_INDEPENDENT)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/pressioopsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/pressioopsConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pressioops)

################################################################################

if(PRESSIO_OPS_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
