cmake_minimum_required(VERSION 3.11)

project(notes CXX)

#------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQIRED ON)

#------------------------------------------------------------------------------

#set(bin_dir bin)
#set(lib_dir lib)
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir}/${lib_dir})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${bin_dir}/${lib_dir})

#------------------------------------------------------------------------------

set(3rd_party_dir ${CMAKE_SOURCE_DIR}/3rd-party)
set(scripts_dir ${CMAKE_SOURCE_DIR}/scripts)
set(targets_dir ${CMAKE_SOURCE_DIR}/src)
set(tests_dir ${CMAKE_SOURCE_DIR}/src/tests)

set(boost_dir C:/libs/boost/boost_1_67_0)

#------------------------------------------------------------------------------

include(${scripts_dir}/cmake/SetupFilters.cmake)

#------------------------------------------------------------------------------

find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

set_property(GLOBAL PROPERTY AUTOGEN_BUILD_DIR gen)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER gen)
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP gen)

#------------------------------------------------------------------------------

include_directories(${boost_dir})

add_subdirectory(${3rd_party_dir}/fmt)
add_subdirectory(${targets_dir}/utils)
add_subdirectory(${targets_dir}/core)
add_subdirectory(${targets_dir}/application)

#------------------------------------------------------------------------------

enable_testing()

add_subdirectory(${3rd_party_dir}/gtest)
add_subdirectory(${tests_dir}/utils_tests)

#------------------------------------------------------------------------------
