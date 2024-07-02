cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

project(root_engine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Tools/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RenderPipeline/")

add_executable(root_engine "${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/main.cpp")

add_executable(render_pipeline_test "${CMAKE_CURRENT_SOURCE_DIR}/RenderPipeline/render_main.cpp")
 # data_types camera render_cache glad ufbx stbi "${CMAKE_CURRENT_SOURCE_DIR}/Tools/third_party/lib/glfw3.lib"
target_link_libraries(render_pipeline_test)


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Testing/")
add_executable(standalone_test "${CMAKE_CURRENT_SOURCE_DIR}/Testing/test_main.cpp")
target_link_libraries(standalone_test data_types)
