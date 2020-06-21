cmake_minimum_required(VERSION 3.11)

project(julie CXX)

#------------------------------------------------------------------------------
# directories
include(LocalConfig.cmake)

set(3rd_party_dir	${CMAKE_SOURCE_DIR}/3rd-party)
set(scripts_dir		${CMAKE_SOURCE_DIR}/scripts)
set(targets_dir		${CMAKE_SOURCE_DIR}/src)
set(tests_dir		${CMAKE_SOURCE_DIR}/src/tests)
set(boost_dir		${local_boost_dir})

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

#------------------------------------------------------------------------------
# setup filters
include(${scripts_dir}/cmake/SetupFilters.cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER cmake_autogen)

set(3rd_party_targets_group	3rd-party)
set(tests_targets_group		tests)

#------------------------------------------------------------------------------
# Qt stuff
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

set_property(GLOBAL PROPERTY AUTOGEN_BUILD_DIR gen)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER gen)
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP gen)

#------------------------------------------------------------------------------
# 3rd-party libs
message("--------------------Loading 3rd-party libs--------------------")

set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)

add_subdirectory(${3rd_party_dir}/fmt)
set_target_properties(fmt PROPERTIES FOLDER ${3rd_party_targets_group})

set(GLM_TEST_ENABLE_CXX_17 ON)
add_subdirectory(${3rd_party_dir}/glm)
set_target_properties(glm_static PROPERTIES FOLDER ${3rd_party_targets_group})

set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_CMAKE_PACKAGE OFF)
set(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
add_subdirectory(${3rd_party_dir}/jsoncpp)
set_target_properties(jsoncpp_lib PROPERTIES FOLDER ${3rd_party_targets_group})

add_subdirectory(${3rd_party_dir}/glad)
set_target_properties(glad PROPERTIES FOLDER ${3rd_party_targets_group})

add_subdirectory(${3rd_party_dir}/assimp)
set_target_properties(assimp PROPERTIES CXX_STANDARD 14)
set_target_properties(assimp PROPERTIES FOLDER ${3rd_party_targets_group}/assimp)
set_target_properties(IrrXML PROPERTIES FOLDER ${3rd_party_targets_group}/assimp)
set_target_properties(zlibstatic PROPERTIES FOLDER ${3rd_party_targets_group}/assimp)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER ${3rd_party_targets_group}/assimp)

#------------------------------------------------------------------------------
# subdirectories
add_subdirectory(${targets_dir}/utils)
add_subdirectory(${targets_dir}/julie)
add_subdirectory(${targets_dir}/app)

#------------------------------------------------------------------------------
# output directories for tests
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${bin_dir}/tests/)
set(CMAKE_PDB_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/${bin_dir}/tests/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/tests/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/${lib_dir}/tests/)

#------------------------------------------------------------------------------
# tests
# function(set_structural_properties target_name folder)
# 	set_target_properties(${target_name} PROPERTIES
# 		RUNTIME_OUTPUT_DIRECTORY	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
# 		LIBRARY_OUTPUT_DIRECTORY	${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
# 		ARCHIVE_OUTPUT_DIRECTORY	${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
# 		PDB_OUTPUT_DIRECTORY		${CMAKE_PDB_OUTPUT_DIRECTORY}
# 		FOLDER						${folder}
# 	)
# endfunction()

# set(gtest_force_shared_crt ON)
# add_subdirectory(${3rd_party_dir}/gtest)
# set_structural_properties(gtest			${tests_targets_group}/gtest)
# set_structural_properties(gtest_main	${tests_targets_group}/gtest)
# set_structural_properties(gmock			${tests_targets_group}/gtest)
# set_structural_properties(gmock_main	${tests_targets_group}/gtest)

# enable_testing()
# add_subdirectory(${tests_dir}/utils_tests)

#------------------------------------------------------------------------------
