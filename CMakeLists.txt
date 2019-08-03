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

add_subdirectory (src/application)
add_subdirectory (src/core)
add_subdirectory (src/utils)

#------------------------------------------------------------------------------

target_include_directories (notes PUBLIC src/core)
target_include_directories (notes PUBLIC src/utils)
target_link_libraries (notes src/core)
target_link_libraries (notes src/utils)

#------------------------------------------------------------------------------
