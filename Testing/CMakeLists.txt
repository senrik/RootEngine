# Testing CMake


add_library(game_world STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/GameWorld.cpp")
target_include_directories(game_world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/GameWorld/")

add_library(roots_obj STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/RootsObj.cpp")
target_include_directories(roots_obj PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
