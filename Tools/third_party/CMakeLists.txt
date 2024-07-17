# Third Party CMake

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/include/glm/")

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/" "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(ufbx STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/ufbx.c")
target_include_directories(ufbx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/UFBX/")

add_library(stbi STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp")
target_include_directories(stbi PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/STBI/")

add_library(glfw INTERFACE)
target_include_directories(glfw SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/")

# GLFW lib Path: ${CMAKE_SOURCE_DIR}/Tools/third_party/lib/glfw3.lib