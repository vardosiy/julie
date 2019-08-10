cmake_minimum_required (VERSION 3.11)

project (notes CXX)

#------------------------------------------------------------------------------

set (BIN_DIR bin)
set (LIB_DIR lib)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BIN_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BIN_DIR}/${LIB_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${BIN_DIR}/${LIB_DIR})

#------------------------------------------------------------------------------

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQIRED ON)

#------------------------------------------------------------------------------

set (3RD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rd-party)

add_subdirectory (${3RD_PARTY_DIR}/fmt)

#------------------------------------------------------------------------------

set (TARGETS_DIR ${CMAKE_SOURCE_DIR}/src)
set (SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/scripts)

add_subdirectory (${TARGETS_DIR}/utils)
add_subdirectory (${TARGETS_DIR}/core)
add_subdirectory (${TARGETS_DIR}/application)

#------------------------------------------------------------------------------
