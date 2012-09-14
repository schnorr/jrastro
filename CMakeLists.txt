# This file is part of JRastro.

# JRastro is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# JRastro is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with JRastro.  If not, see <http://www.gnu.org/licenses/>.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)
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

ADD_SUBDIRECTORY(librastro)

FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES(${JAVA_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${rastro_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${rastro_SOURCE_DIR}/src/)

SET(JRASTRO_LIBRARY_SRC
  src/jrst.c
  src/jrst_cb.c
  src/jrst_trace.c
  src/jrst_functions.c
  src/jrst_filter.c
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
INSTALL(TARGETS jrastro DESTINATION lib)

ADD_EXECUTABLE(jrastro_converter ${JRASTRO_SRC})
TARGET_LINK_LIBRARIES(jrastro_converter rastro)
INSTALL(PROGRAMS ${jrastro_BINARY_DIR}/jrastro_converter DESTINATION bin)
