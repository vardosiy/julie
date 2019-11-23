include(InitSources.cmake)
include(InitHeaders.cmake)

add_library(core STATIC ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(core PUBLIC ${targets_dir}/utils/include)
target_link_libraries(core utils)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)

#------------------------------------------------------------------------------
