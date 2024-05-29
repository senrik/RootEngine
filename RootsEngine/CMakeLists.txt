# Roots Engine CMake

add_library(console STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Console.cpp")
target_include_directories(console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")