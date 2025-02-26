cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(pressioops C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(colors)
include(version)

# define header-only library
#=====================================================================
add_library(pressioops INTERFACE)
target_include_directories(
  pressioops INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install headers
#=====================================================================
include(GNUInstallDirs)
install(
  DIRECTORY include/pressio
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# tests
#=====================================================================
option(PRESSIO_OPS_ENABLE_TESTS "Enable testing for pressio-ops" OFF)
if(PRESSIO_OPS_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
