include(InitSources.cmake)
include(InitHeaders.cmake)
include(InitShaders.cmake)

#------------------------------------------------------------------------------

add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Gui_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")

#qt5_add_resources(QT_RESOURCES resources)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#------------------------------------------------------------------------------

add_executable(notes ${sources} ${headers} ${shaders})

set_target_properties(notes PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------

target_include_directories(notes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(notes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(notes PRIVATE ${targets_dir}/utils/include)
target_link_libraries(notes utils)

target_include_directories(notes PRIVATE ${targets_dir}/core/include)
target_link_libraries(notes core)

target_include_directories(notes PRIVATE ${3rd_party_dir}/glad/include)
target_link_libraries(notes glad)

target_include_directories(notes PRIVATE ${3rd_party_dir}/jsoncpp/include)
target_link_libraries(notes jsoncpp_lib)

target_include_directories(notes PRIVATE ${3rd_party_dir}/glm)
target_link_libraries(notes glm_static)

#target_link_libraries(notes opengl32)

target_include_directories(notes PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})
target_link_libraries(notes Qt5::Widgets Qt5::Gui)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)
add_to_filters(shaders)

#------------------------------------------------------------------------------
