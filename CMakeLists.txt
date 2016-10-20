#==--- Pronto/CMakeLists.txt -----------------------------------------------==#

CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(Pronto)

#==--- Versioning ----------------------------------------------------------==#

SET(Pronto_MAJOR_VERSION 0)
SET(Pronto_MINOR_VERSION 1)
SET(Pronto_PATCH_VERSION 0)
SET(Pronto_VERSION
  ${Pronto_MAJOR_VERSION}.${Pronto_MINOR_VERSION}.${Pronto_PATCH_VERSION}
)

#==--- Directories ---------------------------------------------------------==#

IF(WIN32)
  SET(Pronto_ROOT                      )
  SET(Pronto_TOOLS ${Pronto_ROOT}\tools)
  SET(Blitz_ROOT                       )
ELSE()
  SET(Pronto_ROOT  /opt/pronto         )
  SET(Pronto_TOOLS ${Pronto_ROOT}/tools)
  SET(Blitz_ROOT   /opt/blitz          )
ENDIF()

#==--- FindPackage Path ----------------------------------------------------==#

IF(WIN32)
  LIST(APPEND_CMAKE_MODULE_PATH ${Pronto_TOOLS}\CMake)
ELSE()
  LIST(APPEND CMAKE_MODULE_PATH ${Pronto_TOOLS}/CMake)
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
  INCLUDE_DIRECTORIES(${Pronto_SOURCE_DIR}/include ${Pronto_ROOT}/include)
ENDIF()

#==--- Subdirectories ------------------------------------------------------==#

# Add all subdirectories here.
ADD_SUBDIRECTORY(src)

#==--- Compiler Flags ------------------------------------------------------==#

IF(WIN32)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /O2")
ELSE()
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -g")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pedantic -Wall"  )
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -g -O3"  )
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -pedantic -Wall"    )
ENDIF()

#==--- Asm Flags -----------------------------------------------------------==#

IF(GENERATE_ASM) 
  SET(ASM_FLAGS_REL "-Wa,-anhlds -fverbose-asm -masm=intel" CACHE 
    STRING "Assembly release flags" FORCE)
  SET(ASM_FLAGS_DBG "-Wa,-anhlds -fverbose-asm -masm=intel" CACHE 
    STRING "Assembly debug flags" FORCE)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ASM_FLAGS_REL}")
  SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${ASM_FLAGS_DBG}"  )
ENDIF()

#==--- Set CXXFLAGS --------------------------------------------------------==#

IF(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" 
    CACHE STRING "CXX FLAGS" FORCE)
ELSE()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" 
    CACHE STRING "CXX FLAGS" FORCE)
ENDIF()

#==--- Tests ---------------------------------------------------------------==#

# Add all relevant tests here:
ENABLE_TESTING()
SET(TESTS_STRING "Benchmark")

#==--- Install -------------------------------------------------------------==#

INSTALL(DIRECTORY include/pronto DESTINATION ${Pronto_ROOT}/include/pronto)

#==--- Print Configuration -------------------------------------------------==#
# These are basic options, edit appropriately.

message("#==--- CONFIGURATION --------------------------------------------==#")
message("| PRONTO VERSION          : ${Pronto_VERSION}"                       )
message("| BUILD TYPE              : ${CMAKE_BUILD_TYPE}"                     )
message("| CMAKE_CXX_FLAGS_RELEASE : ${CMAKE_CXX_FLAGS_RELEASE}"              )
message("| CMAKE_CXX_FLAGS_DEBUG   : ${CMAKE_CXX_FLAGS_DEBUG}"                )
message("| CMAKE_CXX_FLAGS         : ${CMAKE_CXX_FLAGS}"                      )
message("| GENERATE ASSEMBLY       : ${GENERATE_ASM}"                         )
message("| TESTS                   : ${TESTS_STRING}"                         )
message("#==--------------------------------------------------------------==#")


