CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(jrastro)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
INCLUDE(CheckLibraryExists)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckFunctionExists)

EXEC_PROGRAM("git --git-dir=${CMAKE_HOME_DIRECTORY}/.git log --oneline -1"
  OUTPUT_VARIABLE "GITVERSION")
EXEC_PROGRAM("git --git-dir=${CMAKE_HOME_DIRECTORY}/.git log -n 1 --format=%ai"
  OUTPUT_VARIABLE "GITDATE")

CONFIGURE_FILE("${jrastro_SOURCE_DIR}/include/jrastro_config.h.in"
               "${CMAKE_BINARY_DIR}/include/jrastro_config.h" @ONLY IMMEDIATE)

FIND_PACKAGE(JNI REQUIRED)
FIND_PACKAGE(RASTRO REQUIRED)
INCLUDE_DIRECTORIES(${JAVA_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${RASTRO_INCLUDE_PATH})
LINK_DIRECTORIES(${RASTRO_LIBRARY_PATH})

SET(JRASTRO_LIBRARY_SRC
  src/jrst.c
  src/jrst_cb.c
  src/jrst_trace.c
  src/jrst_functions.c
)

SET(JRASTRO_SRC
  src/converter/jrastro_converter.c
  src/converter/jrastro_paje.c
)

INCLUDE_DIRECTORIES(${jrastro_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${jrastro_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include/)

ADD_LIBRARY(jrastro SHARED ${JRASTRO_LIBRARY_SRC})
TARGET_LINK_LIBRARIES(jrastro rastro)

ADD_EXECUTABLE(jrastro_converter ${JRASTRO_SRC})
TARGET_LINK_LIBRARIES(jrastro_converter rastro)

