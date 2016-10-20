#==--- Pronto/src/CMakeLists.txt --------------------------------------==#

#==--- Boost ---------------------------------------------------------------==#

INCLUDE_DIRECTORIES(
  ${Blitz_ROOT}/include
  ${Pronto_SOURCE_DIR}/include)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

SET(TEST_BIN_DIR ${Pronto_SOURCE_DIR}/bin     )
SET(ASM_DIR      ${Pronto_SOURCE_DIR}/assembly)

#==--- Make Test Function --------------------------------------------------==#

FUNCTION(MakeTest TestName TestFiles TestLibs TestBinDir)
  ADD_EXECUTABLE(${${TestName}} ${${TestFiles}})

  TARGET_LINK_LIBRARIES(${${TestName}} ${${TestLibs}})

  # Move test binary to the correct directory
  SET_TARGET_PROPERTIES(${${TestName}} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    ${${TestBinDir}})

  ADD_TEST(NAME ${${TestName}} WORKING_DIRECTORY ${${TestBinDir}} COMMAND
    ${${TestBinDir}}/${${TestName}})
ENDFUNCTION()

FUNCTION(MakeAsm AsmName AsmInputFiles AsmLibs AsmDir)
  ADD_EXECUTABLE(${${AsmName}} ${${AsmInputFiles}})

  TARGET_LINK_LIBRARIES(${${AsmName}} ${${AsmLibs}})

  SET_TARGET_PROPERTIES(${${AsmName}} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    ${${AsmDir}})
ENDFUNCTION()

#==--- Benchmark Tests -----------------------------------------------------==#

SET(SOURCES )
SET(TEST_NAME  BenchmarkTests)
SET(TEST_FILES BenchmarkTests.cpp ${SOURCES})
SET(TEST_LIBS -L/opt/blitz/lib -lblitz)

MakeTest(TEST_NAME TEST_FILES TEST_LIBS TEST_BIN_DIR)

IF(GENERATE_ASM)
  set(ASM_NAME  BenchmarkTestsAsm)
  set(ASM_FILES BenchmarkTests.cc)
  set(ASM_LIBS  ${TEST_LIBS})
  MakeAsm(ASM_NAME ASM_FILES ASM_LIBS ASM_DIR)
ENDIF()

#==-------------------------------------------------------------------------==#
