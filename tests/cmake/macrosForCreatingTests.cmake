
macro(add_serial_exe_and_fake_test_just_for_running TESTNAME TESTSRCS)
  set(testNameFinal ${TESTNAME})
  add_executable(${testNameFinal} ${TESTSRCS})
  target_include_directories(${testNameFinal} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  add_test(NAME ${testNameFinal} COMMAND ${testNameFinal})
endmacro()
#=====================================================================

macro(add_mpi_exe_and_fake_test_just_for_running TESTNAME TESTSRCS nRANKS)
  set(testNameFinal ${TESTNAME}_np${nRANKS})
  add_executable(${testNameFinal} ${TESTSRCS})
  target_include_directories(${testNameFinal} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(${testNameFinal} ${MPI_CXX_LIBRARIES})
  add_test(
    NAME ${testNameFinal}
    COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${nRANKS}
    ${MPIEXEC_PREFLAGS} ${testNameFinal} ${MPIEXEC_POSTFLAGS}
    )
endmacro()
#=====================================================================
