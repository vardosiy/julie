cmake_minimum_required(VERSION 3.11)

project(julie CXX)

#------------------------------------------------------------------------------
# directories
set(3rd_party_dir	${CMAKE_SOURCE_DIR}/3rd-party)
set(scripts_dir		${CMAKE_SOURCE_DIR}/scripts)
set(targets_dir		${CMAKE_SOURCE_DIR}/src)
set(tests_dir		${CMAKE_SOURCE_DIR}/src/tests)
set(boost_dir		C:/libs/boost/boost_1_67_0)

set(bin_dir			bin)
set(lib_dir			lib)

#------------------------------------------------------------------------------
# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQIRED ON)

#add_compile_options(-Wall -Wshadow)

#------------------------------------------------------------------------------
# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${bin_dir}/)
set(CMAKE_PDB_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/${bin_dir}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/)

# temp
set(CMAKE_INSTALL_PREFIX			${CMAKE_SOURCE_DIR}/TEST)
set(CMAKE_INSTALL_LIBDIR			lib)

#------------------------------------------------------------------------------
# setup filters
include(${scripts_dir}/cmake/SetupFilters.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER cmake_autogen)
set(3rd_party_targets_group 3rd-party)
set(tests_targets_group tests)

#------------------------------------------------------------------------------
# Qt stuff
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

set_property(GLOBAL PROPERTY AUTOGEN_BUILD_DIR gen)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER gen)
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP gen)

#------------------------------------------------------------------------------

#find_package(OpenGL REQUIRED)

#------------------------------------------------------------------------------
# 3rd-party libs
message("\nLoading 3rd-party libs")

include_directories(${boost_dir})

add_subdirectory(${3rd_party_dir}/fmt)
set_target_properties(fmt PROPERTIES FOLDER ${3rd_party_targets_group})

add_subdirectory(${3rd_party_dir}/glm)
set_target_properties(glm_static PROPERTIES FOLDER ${3rd_party_targets_group})

add_subdirectory(${3rd_party_dir}/jsoncpp)
set_target_properties(jsoncpp_lib PROPERTIES FOLDER ${3rd_party_targets_group})

add_subdirectory(${3rd_party_dir}/glad)
set_target_properties(glad PROPERTIES FOLDER ${3rd_party_targets_group})

#------------------------------------------------------------------------------
# subdirectories
add_subdirectory(${targets_dir}/utils)
add_subdirectory(${targets_dir}/renderer)
add_subdirectory(${targets_dir}/application)

#------------------------------------------------------------------------------
# output directories for tests
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${bin_dir}/tests/)
set(CMAKE_PDB_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/${bin_dir}/tests/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/tests/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/tests/)

#------------------------------------------------------------------------------
# tests
add_subdirectory(${3rd_party_dir}/gtest)
set_target_properties(gtest			PROPERTIES FOLDER ${tests_targets_group}/gtest)
set_target_properties(gtest_main	PROPERTIES FOLDER ${tests_targets_group}/gtest)
set_target_properties(gmock			PROPERTIES FOLDER ${tests_targets_group}/gtest)
set_target_properties(gmock_main	PROPERTIES FOLDER ${tests_targets_group}/gtest)

enable_testing()
add_subdirectory(${tests_dir}/utils_tests)

#------------------------------------------------------------------------------
