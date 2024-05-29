# Testing CMake


add_library(game_world STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/GameWorld.cpp")
target_include_directories(game_world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(shader STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp")
target_include_directories(shader PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
