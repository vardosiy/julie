set (SOURCES)
include (InitSources.cmake)

add_library(core STATIC ${SOURCES})

#------------------------------------------------------------------------------

target_include_directories (core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

target_include_directories (core PUBLIC ${TARGETS_DIR}/utils/include)
target_link_libraries (core utils)

#------------------------------------------------------------------------------

include (${SCRIPTS_DIR}/cmake/SetupFilters.cmake)

#------------------------------------------------------------------------------
