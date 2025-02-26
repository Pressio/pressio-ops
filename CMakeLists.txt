cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(pressio C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(colors)
include(version)

# install headers
#=====================================================================
include(GNUInstallDirs)
install(
  DIRECTORY include/pressio
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# tests
#=====================================================================
if(PRESSIO_OPS_ENABLE_TESTS)
  add_library(pressioops INTERFACE)

  target_include_directories(
    pressioops INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

  enable_testing()
  add_subdirectory(tests)
endif()
