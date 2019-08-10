set (SOURCES)
include (InitSources.cmake)

add_library(utils STATIC ${SOURCES})

#------------------------------------------------------------------------------

target_include_directories (utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

target_include_directories (utils PUBLIC ${3RD_PARTY_DIR}/fmt/include)
target_link_libraries (utils fmt)

#------------------------------------------------------------------------------

include (${SCRIPTS_DIR}/cmake/SetupFilters.cmake)

#------------------------------------------------------------------------------
