#==--- Jolt/CMakeLists.txt -------------------------------------------------==#

CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(Jolt)

#==--- Versioning ----------------------------------------------------------==#

SET(Jolt_MAJOR_VERSION 0)
SET(Jolt_MINOR_VERSION 1)
SET(Jolt_PATCH_VERSION 0)
SET(Jolt_VERSION
  ${Jolt_MAJOR_VERSION}.${Jolt_MINOR_VERSION}.${Jolt_PATCH_VERSION}
)

#==--- Directories ---------------------------------------------------------==#

IF(WIN32)
  SET(Jolt_ROOT                    )
  SET(Jolt_TOOLS ${Jolt_ROOT}\tools)
  SET(Blitz_ROOT                   )
ELSE()
  SET(Jolt_ROOT  /opt/jolt         )
  SET(Jolt_TOOLS ${Jolt_ROOT}/tools)
  SET(Blitz_ROOT /opt/blitz        )
ENDIF()

#==--- FindPackage Path ----------------------------------------------------==#

IF(WIN32)
  LIST(APPEND_CMAKE_MODULE_PATH ${Jolt_TOOLS}\CMake)
ELSE()
  LIST(APPEND CMAKE_MODULE_PATH ${Jolt_TOOLS}/cmake)
ENDIF()

#==--- Build Type ----------------------------------------------------------==#

IF(NOT CMAKE_BUILD_TYPE) 
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type not specified!")
ENDIF(NOT CMAKE_BUILD_TYPE)

#==--- Commandline Options -------------------------------------------------==#

# Define all command line options here:
OPTION(GENERATE_ASM "Generate assembly code"  OFF)

#==--- Include directories -------------------------------------------------==#

# Define all include directories here:
IF(WIN32)
ELSE()
  INCLUDE_DIRECTORIES(${Jolt_SOURCE_DIR}/include ${Jolt_ROOT}/include)
ENDIF()

#==--- Subdirectories ------------------------------------------------------==#

# Add all subdirectories here.
ADD_SUBDIRECTORY(src)

#==--- Number of processors : CPU ------------------------------------------==#

SET(CPU_DETECTED "YES" CACHE STRING "CPU Detected" FORCE)
SET(PROC_COUNT   0     CACHE STRING "Detecting Processor Count" FORCE)
ADD_DEFINITIONS(-DCPU_DETECTED)

# LINUX: Note that this will find the number of PHYSICAL cores ONLY, since we
#        only want to parallelize across PHYSICAL cores!
SET(CPUINFO_FILE "/proc/cpuinfo")
IF(EXISTS "${CPUINFO_FILE}")
  EXEC_PROGRAM(cat ARGS "/proc/cpuinfo | grep 'cpu cores'" 
    OUTPUT_VARIABLE CPU_INFO)
  STRING(REGEX MATCH "[0-9]+" PROCESSOR_COUNT ${CPU_INFO})
  SET(PROC_COUNT ${PROCESSOR_COUNT} CACHE STRING "Num Processors" FORCE)
ENDIF()

# APPLE:
IF(APPLE)
  EXEC_PROGRAM(sysctl ARGS "-a | grep machdep.cpu" OUTPUT_VARIABLE CPU_INFO)
  STRING(REGEX MATCH "core_count: [0-9]+" PROC_STRING ${CPU_INFO})
  STRING(REGEX MATCH "[0-9]+" PROCESSOR_COUNT ${PROC_STRING})
  SET(PROC_COUNT ${PROCESSOR_COUNT} CACHE STRING "Num Processors" FORCE)
ENDIF(APPLE)

# Windows:
IF(WIN32)
  SET(PROC_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
ENDIF()

ADD_DEFINITIONS(-DCPU_CORES=${PROC_COUNT})

#==--- Vector instructions : CPU -------------------------------------------==#

SET(ENABLE_AVX TRUE)
SET(ENABLE_SSE TRUE)

IF(APPLE)
  STRING(REGEX MATCH "SSE" SSE_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "SSE" "{SSE_FOUND}" SSE_TRUE)

  STRING(REGEX MATCH "SSE2" SSE2_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "SSE2" "${SSE2_FOUND}" SSE2_TRUE)

  STRING(REGEX MATCH "SSSE3" SSSE3_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "SSSE3" "${SSSE3_FOUND}" SSSE3_TRUE)

  STRING(REGEX MATCH "SSE4.1" SSE41_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "SSE4.1" "${SSE41_FOUND}" SSE41_TRUE)

  STRING(REGEX MATCH "SSE4.2" SSE4,2_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "SSE4.2" "${SSE42_FOUND}" SSE42_TRUE)

  STRING(REGEX MATCH "AVX1.0" AVX1_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "AVX1.0" "${AVX1_FOUND}" AVX1_TRUE)

  STRING(REGEX MATCH "AVX2.0" AVX2_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "AVX2.0" "${AVX2_FOUND}" AVX2_TRUE)
ENDIF(APPLE)

IF(UNIX AND NOT APPLE)
  EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPU_INFO)

  STRING(REGEX MATCH "sse" SSE_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "sse" "${SSE_FOUND}" SSE_TRUE)

  STRING(REGEX MATCH "sse2" SSE2_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "sse2" "${SSE2_FOUND}" SSE2_TRUE)

  # /proc/cpuinfo apparently omits sse3 :( bad luck atm!

  STRING(REGEX MATCH "ssse3" SSSE3_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "ssse3" "${SSSE3_FOUND}" SSSE3_TRUE)

  STRING(REGEX MATCH "sse4_1" SSE41_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "sse4_1" "${SSE41_FOUND}" SSE41_TRUE)

  STRING(REGEX MATCH "sse4_2" SSE42_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "sse4_2" "${SSE42_FOUND}" SSE42_TRUE)

  STRING(REGEX MATCH "avx" AVX1_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "avx" "${AVX1_FOUND}" AVX1_TRUE)

  STRING(REGEX MATCH "avx2" AVX2_FOUND ${CPU_INFO})
  STRING(COMPARE EQUAL "avx2" "${AVX2_FOUND}" AVX2_TRUE)
ENDIF(UNIX AND NOT APPLE)

# Check which vectorized instructions were found and add them:
IF(AVX2_TRUE AND ENABLE_AVX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")
  SET(VEC_INSTRUCS "AVX2")
  ADD_DEFINITIONS(-DAVX2)
ELSEIF(AVX1_TRUE AND ENABLE_AVX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
  SET(VEC_INSTRUCS "AVX1")
  ADD_DEFINITIONS(-DAVX1)
ELSEIF(SSE42_TRUE AND ENABLE_SSE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")
  SET(VEC_INSTRUCS "SSE42")
  ADD_DEFINITIONS(-SSE42)
ELSEIF(SSE41_TRUE AND ENABLE_SSE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
  SET(VEC_INSTRUCS "SSE41")
  ADD_DEFINITIONS(-SSE41)
ELSEIF(SSSE3_TRUE AND ENABLE_SSE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3")
  SET(VEC_INSTRUCS "SSSE3")
  ADD_DEFINITIONS(-SSSE3)
ELSEIF(SSE2_TRUE AND ENABLE_SSE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
  SET(VEC_INSTRUCS "SSE2")
  ADD_DEFINITIONS(-SSE2)
ELSEIF(SSE_TRUE AND ENABLE_SSE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
  SET(VEC_INSTRUCS "SSE")
  ADD_DEFINITIONS(-SSE)
ELSE(AVX2_TRUE AND ENABLE_AVX)

ENDIF(AVX2_TRUE AND ENABLE_AVX)

#==--- Compiler Flags ------------------------------------------------------==#

IF(WIN32)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /O2"  )
ELSE()
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z"     )
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pedantic -Wall")
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -std=c++1z -O3"   )
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -pedantic -Wall"  )
ENDIF()

#==--- Asm Flags -----------------------------------------------------------==#

IF(GENERATE_ASM) 
  SET(ASM_FLAGS "-Wa,-anhlds -fverbose-asm -masm=intel" CACHE 
    STRING "Assembly release flags" FORCE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ASM_FLAGS}")
ENDIF()

#==--- Set CXXFLAGS --------------------------------------------------------==#

IF(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}" CACHE
    STRING "CXX Flags" FORCE)
ELSE()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}" CACHE
    STRING "CXX Flags" FORCE)
ENDIF()

#==--- Tests ---------------------------------------------------------------==#

# Add all relevant tests here:
ENABLE_TESTING()
SET(TESTS_STRING "Benchmark")

#==--- Install -------------------------------------------------------------==#

INSTALL(DIRECTORY include/Jolt DESTINATION ${Jolt_ROOT}/include/jolt)

#==--- Print Configuration -------------------------------------------------==#
# These are basic options, edit appropriately.

message("#==--- CONFIGURATION --------------------------------------------==#")
message("| JOLT VERSION            : ${Jolt_VERSION}"                         )
message("| BUILD TYPE              : ${CMAKE_BUILD_TYPE}"                     )
message("| USING CPU               : ${CPU_DETECTED}"                         )
message("| PROCESSORS              : ${PROC_COUNT}"                           )
message("| VECTOR INSTRUCTIONS     : ${VEC_INSTRUCS}"                         )
message("| CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}"              )
message("| CMAKE_CXX_FLAGS_DEBUG   : ${CMAKE_CXX_FLAGS_DEBUG}"                )
message("| CMAKE_CXX_FLAGS         : ${CMAKE_CXX_FLAGS}"                      )
message("| GENERATE ASSEMBLY       : ${GENERATE_ASM}"                         )
message("| TESTS                   : ${TESTS_STRING}"                         )
message("#==--------------------------------------------------------------==#")


