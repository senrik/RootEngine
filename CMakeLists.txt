cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
project(roots_engine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/rootengine-tools/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RootsEngine/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/rootengine-renderpipeline/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Testing/")