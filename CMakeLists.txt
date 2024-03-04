cmake_minimum_required(CMAKE_VERSION 3.10)

project(root_engine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Render\sPipeline/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/")

add_executable(root_engine "${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/main")