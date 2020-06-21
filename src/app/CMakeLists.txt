include(Autogen.cmake)

#------------------------------------------------------------------------------

add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Gui_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#------------------------------------------------------------------------------

add_executable(app ${sources} ${headers} ${ui_sources} ${shaders})

set_target_properties(app PROPERTIES AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/res/ui)
set_target_properties(app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(app glad)
target_link_libraries(app utils)
target_link_libraries(app julie)

target_include_directories(app PUBLIC ${boost_dir})

target_include_directories(app PRIVATE ${3rd_party_dir}/jsoncpp/include)
target_link_libraries(app jsoncpp_lib)

target_include_directories(app PRIVATE ${3rd_party_dir}/glm)
target_link_libraries(app glm_static)

target_include_directories(app PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})
target_link_libraries(app Qt5::Widgets Qt5::Gui)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)
add_to_filters(ui_sources)
add_to_filters(shaders)

#------------------------------------------------------------------------------
