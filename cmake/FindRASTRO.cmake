#
# Find the RASTRO libraries and include dir
#

# RASTRO_INCLUDE_PATH  - Directories to include to use RASTRO
# RASTRO_LIBRARY_PATH    - Files to link against to use RASTRO
# RASTRO_FOUND        - When false, don't try to use RASTRO
#
# RASTRO_PATH can be used to make it simpler to find the various include
# directories and compiled libraries when RASTRO was not installed in the
# usual/well-known directories (e.g. because you made an in tree-source
# compilation or because you installed it in an "unusual" directory).
# Just set RASTRO_PATH it to your specific installation directory
#
FIND_LIBRARY(RASTRO_LIBRARY
  NAMES rastro
  PATHS /usr/lib /usr/local/lib ${RASTRO_PATH}/lib ${RASTRO_PATH}/x86_64/lib/)

IF(RASTRO_LIBRARY)
  MESSAGE ( STATUS "Found RASTRO: ${RASTRO_LIBRARY}" )
  GET_FILENAME_COMPONENT(RASTRO_LIBRARY_tmp "${RASTRO_LIBRARY}" PATH)
  SET (RASTRO_LIBRARY_PATH ${RASTRO_LIBRARY_tmp} CACHE PATH "")
ELSE(RASTRO_LIBRARY)
  SET (RASTRO_LIBRARY_PATH "RASTRO_LIBRARY_PATH-NOTFOUND")
  unset(LIBRARY_PATH CACHE)
ENDIF(RASTRO_LIBRARY)

FIND_PATH( RASTRO_INCLUDE_tmp rastro.h
  PATHS
  ${RASTRO_GUESSED_INCLUDE_PATH}
  ${RASTRO_PATH}/include
  /usr/include
  /usr/local/include
)

IF(RASTRO_INCLUDE_tmp)
  SET (RASTRO_INCLUDE_PATH "${RASTRO_INCLUDE_tmp}" CACHE PATH "")
ELSE(RASTRO_INCLUDE_tmp)
  SET (RASTRO_INCLUDE_PATH "RASTRO_INCLUDE_PATH-NOTFOUND")
ENDIF(RASTRO_INCLUDE_tmp)

IF( RASTRO_INCLUDE_PATH )
  IF( RASTRO_LIBRARY_PATH )
    SET( RASTRO_FOUND TRUE )
  ENDIF ( RASTRO_LIBRARY_PATH )
ENDIF( RASTRO_INCLUDE_PATH )

IF( NOT RASTRO_FOUND )
  MESSAGE(STATUS "RASTRO installation was not found. Please provide RASTRO_PATH:")
  MESSAGE(STATUS "  - through the GUI when working with ccmake, ")
  MESSAGE(STATUS "  - as a command line argument when working with cmake e.g.")
  MESSAGE(STATUS "    cmake .. -DRASTRO_PATH:PATH=/usr/local/tau ")
  SET(RASTRO_PATH "" CACHE PATH "Root of RASTRO install tree." )
ENDIF( NOT RASTRO_FOUND )

unset(RASTRO_INCLUDE_tmp CACHE)
mark_as_advanced(RASTRO_LIBRARY)
