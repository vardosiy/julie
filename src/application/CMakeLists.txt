include(InitSources.cmake)
include(InitHeaders.cmake)
include(InitShaders.cmake)

#------------------------------------------------------------------------------

add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Gui_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#------------------------------------------------------------------------------

add_executable(julie ${sources} ${headers} ${shaders})

set_target_properties(julie PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------

target_include_directories(julie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(julie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(julie glad)
target_link_libraries(julie utils)
target_link_libraries(julie renderer)

target_include_directories(julie PRIVATE ${3rd_party_dir}/jsoncpp/include)
target_link_libraries(julie jsoncpp_lib)

target_include_directories(julie PRIVATE ${3rd_party_dir}/glm)
target_link_libraries(julie glm_static)

target_include_directories(julie PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})
target_link_libraries(julie Qt5::Widgets Qt5::Gui)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)
add_to_filters(shaders)

#------------------------------------------------------------------------------
