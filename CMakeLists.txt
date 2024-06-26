cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)

project(root_engine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Tools/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RenderPipeline/")

add_executable(root_engine "${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/main.cpp")

project(render_pipeline_test)
add_executable(render_pipeline_test "${CMAKE_CURRENT_SOURCE_DIR}/RenderPipeline/render_main.cpp")

target_link_libraries(render_pipeline_test camera render_obj glad ufbx stbi "${CMAKE_CURRENT_SOURCE_DIR}/Tools/third_party/lib/glfw3.lib")


project(standalone_test)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Testing/")
add_executable(standalone_test "${CMAKE_CURRENT_SOURCE_DIR}/Testing/test_main.cpp")
target_link_libraries(standalone_test game_world asset_io)