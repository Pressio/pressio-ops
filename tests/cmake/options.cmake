
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

# tpls
#=====================================================================
option(PRESSIO_ENABLE_TPL_EIGEN		  "Enable Eigen TPL"	  OFF)
option(PRESSIO_ENABLE_TPL_TRILINOS	"Enable Trilinos TPL"	OFF)
option(PRESSIO_ENABLE_TPL_KOKKOS		"Enable Kokkos TPL"	  OFF)
option(PRESSIO_ENABLE_TPL_MPI		    "Enable MPI"	      	OFF)

if(PRESSIO_ENABLE_TPL_EIGEN)
  message(">> Enabling Eigen since PRESSIO_ENABLE_TPL_EIGEN=ON")
  add_definitions(-DPRESSIO_ENABLE_TPL_EIGEN)

  if(EIGEN_INCLUDE_DIR)
    include_directories(SYSTEM ${EIGEN_INCLUDE_DIR})
  else()
    find_package(Eigen3)

    if(NOT EIGEN3_FOUND)
      # TODO: use FetchContent_Declare instead of failing?
      message(FATAL_ERROR
      "I cannot find the Eigen headers. "
      "Please reconfigure with: -DEIGEN_INCLUDE_DIR=<full-path-to-headers>")
    endif()

    include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
  endif()
endif()

# if trilinos is on, then also set MPI, BLAS, LAPACK and KOKKOS ON
if(PRESSIO_ENABLE_TPL_TRILINOS)
  message(">> PRESSIO_ENABLE_TPL_TRILINOS=ON ==> enabling also BLAS, LAPACK, MPI, KOKKOS")
  add_definitions(-DPRESSIO_ENABLE_TPL_TRILINOS)

  set(PRESSIO_ENABLE_TPL_KOKKOS ON)
  set(PRESSIO_ENABLE_TPL_MPI ON)

  find_package(Trilinos REQUIRED)
  # TODO: it is possible to use find_package(<PackageName>) for each (sub)package
  # https://trilinos.github.io/pdfs/Finding_Trilinos.txt
  include_directories(SYSTEM ${Trilinos_INCLUDE_DIRS})
  link_libraries(${Trilinos_LIBRARIES})
endif()

if(PRESSIO_ENABLE_TPL_KOKKOS)
  message(">> Enabling Kokkos since PRESSIO_ENABLE_TPL_KOKKOS=ON")
  add_definitions(-DPRESSIO_ENABLE_TPL_KOKKOS)

  # if kokkos is used as standalone lib, then user
  # needs to define: Kokkos_ROOT and KokkosKernels_ROOT
  if(NOT PRESSIO_ENABLE_TPL_TRILINOS)
    if (NOT Kokkos_ROOT OR NOT KokkosKernels_ROOT)
      message(
	FATAL_ERROR
	"Missing Kokkos installation directories. KOKKOS needs:
        -D Kokkos_ROOT=<full-path-to-kokkos-installation>
        -D KokkosKernels_ROOT=<full-path-to-kokkos-kernels-installation>"
      )
    endif()

    find_package(Kokkos REQUIRED)
    find_package(KokkosKernels REQUIRED)
    link_libraries(Kokkos::kokkos Kokkos::kokkoskernels)
  endif()
endif()

if(PRESSIO_ENABLE_TPL_MPI)
  message(">> Enabling MPI since PRESSIO_ENABLE_TPL_MPI=ON")
  add_definitions(-DPRESSIO_ENABLE_TPL_MPI)
  find_package(MPI REQUIRED)
  include_directories(SYSTEM ${MPI_CXX_INCLUDE_DIRS})
endif()
