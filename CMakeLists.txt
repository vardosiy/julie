cmake_minimum_required(VERSION 3.11)

project(notes CXX)

#------------------------------------------------------------------------------

set(bin_dir bin)
set(lib_dir lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir}/${lib_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir}/${lib_dir})

#------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQIRED ON)

#------------------------------------------------------------------------------

set(3rd_party_dir ${CMAKE_SOURCE_DIR}/3rd-party)
set(scripts_dir ${CMAKE_SOURCE_DIR}/scripts)
set(targets_dir ${CMAKE_SOURCE_DIR}/src)

#------------------------------------------------------------------------------

include(${scripts_dir}/cmake/SetupFilters.cmake)

#------------------------------------------------------------------------------

find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

add_subdirectory(${3rd_party_dir}/fmt)
add_subdirectory(${targets_dir}/utils)
add_subdirectory(${targets_dir}/core)
add_subdirectory(${targets_dir}/application)

#------------------------------------------------------------------------------
