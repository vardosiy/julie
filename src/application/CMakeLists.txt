set (SOURCES)
include (InitSources.cmake)

add_executable (notes ${SOURCES})

#------------------------------------------------------------------------------

target_include_directories (notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

target_include_directories (notes PUBLIC ${TARGETS_DIR}/utils/include)
target_link_libraries (notes utils)

target_include_directories (notes PUBLIC ${TARGETS_DIR}/core/include)
target_link_libraries (notes core)

#------------------------------------------------------------------------------

include (${SCRIPTS_DIR}/cmake/SetupFilters.cmake)

#------------------------------------------------------------------------------
