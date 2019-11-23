include(InitSources.cmake)
include(InitHeaders.cmake)

add_library(glad STATIC ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)

#------------------------------------------------------------------------------
