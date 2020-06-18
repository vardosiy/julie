include(Autogen.cmake)

add_library(julie STATIC ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(julie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(julie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(julie utils)
target_link_libraries(julie glad)

target_include_directories(julie PUBLIC ${3rd_party_dir}/glm)
target_link_libraries(julie glm_static)

target_include_directories(julie PRIVATE ${3rd_party_dir}/jsoncpp/include)
target_link_libraries(julie jsoncpp_lib)

target_include_directories(julie PRIVATE ${3rd_party_dir}/assimp/include)
target_link_libraries(julie assimp)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)

#------------------------------------------------------------------------------
