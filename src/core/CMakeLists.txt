cmake_minimum_required (VERSION 3.11)

project (core CXX)

#------------------------------------------------------------------------------

add_library(core STATIC )

#------------------------------------------------------------------------------

target_include_directories (notes PUBLIC lib/src)
target_link_libraries (notes utilities)

#------------------------------------------------------------------------------
