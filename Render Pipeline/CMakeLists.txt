add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third\sparty/include/glm/")

add_library(renderer STATIC "${CMAKE_CURRENT_SOURCE_DIR}/render_pipeline.cpp")

add_library(camera STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp")

target_include_directories(camera PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(ufbx STATIC "${CMAKE_CURRENT_SOURCE_DIR}/third\sparty/src/ufbx.c")
target_include_directories(ufbx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third\sparty/include/")

add_library(stbi STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp")
target_include_directories(stbi PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third\sparty/include/")




