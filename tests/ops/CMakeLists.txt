
# to include google test fixtures
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/fixtures)

if(PRESSIO_ENABLE_TPL_EIGEN)
  add_serial_utest(
    ops_eigen
    ops_eigen_vector.cc
    ops_eigen_matrix.cc
    ops_eigen_diag.cc
    ops_eigen_column.cc
    ops_eigen_span.cc
    ops_eigen_subspan.cc
    ops_eigen_level2.cc
    ops_eigen_level3.cc
    ops_hello_world_1.cc
  )

  add_serial_exe_and_fake_test_just_for_running(
    hello_world_1 ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_1.cc
  )
endif()

if(PRESSIO_ENABLE_TPL_KOKKOS)
  add_serial_utest_kokkos(ops_vector_kokkos
    ops_kokkos_vector.cc
    ops_kokkos_matrix.cc
    ops_kokkos_diag.cc
    ops_kokkos_span.cc
    ops_kokkos_subspan.cc
    ops_kokkos_level2.cc
    ops_kokkos_level3.cc
  )
endif()

if(PRESSIO_ENABLE_TPL_TRILINOS)
  add_mpi_exe_and_fake_test_just_for_running(
    hello_world_2 ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_2.cc 3
  )

  # TPETRA
  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_vector.cc)
  add_utest_mpi(ops_vector_tpetra gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_multi_vector.cc)
  add_utest_mpi(ops_multi_vector_tpetra gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_level2.cc)
  add_utest_mpi(ops_level2_tpetra gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_level3.cc)
  add_utest_mpi(ops_level3_tpetra gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_column_expr.cc)
  add_utest_mpi(ops_column_expr_tpetra gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_hello_world_2.cc)
  add_utest_mpi(ops_hello_world_2 gTestMain_tpetra 3 "${SRC1}")


  # TPETRA BLOCK
  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_block_vector.cc)
  add_utest_mpi(ops_vector_tpetra_block gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_block_column_expr.cc)
  add_utest_mpi(ops_column_expr_tpetra_block gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_block_multi_vector.cc)
  add_utest_mpi(ops_multi_vector_tpetra_block gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_block_level2.cc)
  add_utest_mpi(ops_level2_tpetra_block gTestMain_tpetra 3 "${SRC1}")

  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_tpetra_block_level3.cc)
  add_utest_mpi(ops_level3_tpetra_block gTestMain_tpetra 3 "${SRC1}")

  # TEUCHOS
  set(SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/ops_teuchos_vector.cc)
  add_serial_utest(ops_vector_teuchos "${SRC1}")

endif()
