cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(pressioops C CXX)

# tests
#=====================================================================
option(PRESSIO_OPS_ENABLE_TESTS "Enable testing for pressio-ops" OFF)
if(PRESSIO_OPS_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
