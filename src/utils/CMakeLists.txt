include(Sources.cmake)
include(Headers.cmake)

add_library(utils STATIC ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(utils PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(utils PUBLIC ${3rd_party_dir}/fmt/include)
target_link_libraries(utils fmt)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)

#------------------------------------------------------------------------------
