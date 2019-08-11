include(InitSources.cmake)
include(InitResources.cmake)
include(InitUiSources.cmake)

#------------------------------------------------------------------------------

add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
qt5_add_resources(QT_RESOURCES resources)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#------------------------------------------------------------------------------

add_executable(notes ${sources} ${resources} ${ui_sources})

#------------------------------------------------------------------------------

target_include_directories(notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(notes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

target_include_directories(notes PUBLIC ${targets_dir}/utils/include)
target_link_libraries(notes utils)

target_include_directories(notes PUBLIC ${targets_dir}/core/include)
target_link_libraries(notes core)

target_include_directories(notes PUBLIC ${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
target_link_libraries(notes Qt5::Widgets Qt5::Qml Qt5::Quick)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(resources)
add_to_filters(ui_sources)

#------------------------------------------------------------------------------
