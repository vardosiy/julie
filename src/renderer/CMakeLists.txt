include(Autogen.cmake)

add_library(renderer STATIC ${sources} ${headers})

#------------------------------------------------------------------------------

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(renderer utils)
target_link_libraries(renderer glad)

target_include_directories(renderer PUBLIC ${3rd_party_dir}/glm)
target_link_libraries(renderer glm_static)

target_include_directories(renderer PRIVATE ${3rd_party_dir}/jsoncpp/include)
target_link_libraries(renderer jsoncpp_lib)

target_include_directories(renderer PRIVATE ${3rd_party_dir}/assimp/include)
target_link_libraries(renderer assimp)

#------------------------------------------------------------------------------

add_to_filters(sources)
add_to_filters(headers)

#------------------------------------------------------------------------------
