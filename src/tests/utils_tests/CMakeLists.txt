include(Autogen.cmake)

add_executable(utils_tests ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(utils_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fixtures)
target_include_directories(utils_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(utils_tests PUBLIC ${3rd_party_dir}/gtest)
target_link_libraries(utils_tests gtest gtest_main)

target_include_directories(utils_tests PUBLIC ${targets_dir}/utils/include)
target_link_libraries(utils_tests utils)

add_test(utils_tests utils_tests)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)
set_target_properties(utils_tests PROPERTIES FOLDER ${tests_targets_group})

#------------------------------------------------------------------------------
