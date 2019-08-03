cmake_minimum_required (VERSION 3.9)

project (notes VERSION 0.1 LANGUAGES CXX)

#------------------------------------------------------------------------------

add_executable (notes app/main.cpp)
add_subdirectory (core)

#------------------------------------------------------------------------------

target_include_directories (notes PUBLIC lib/src)
target_link_libraries (notes utilities)

#------------------------------------------------------------------------------
