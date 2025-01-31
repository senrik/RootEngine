# RootsEngine CMake

add_library(console STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Console/Console.cpp")
target_include_directories(console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Console/include/")


add_executable(roots_engine "${CMAKE_CURRENT_SOURCE_DIR}/roots-engine_main.cpp")
