include(InitSources.cmake)

add_library(core STATIC ${sources})

#------------------------------------------------------------------------------

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

target_include_directories(core PUBLIC ${TARGETS_DIR}/utils/include)
target_link_libraries(core utils)

#------------------------------------------------------------------------------

add_to_filters(sources)

#------------------------------------------------------------------------------
