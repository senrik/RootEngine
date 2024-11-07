# Third Party CMake


## GLFW3
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

execute_process (
    COMMAND cmake ./glfw/ -B ./glfw/build/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GLFW_OUTPUT
)
message(STATUS "[Tools] GLFW CMake:\n${GLFW_OUTPUT}")

execute_process (
    COMMAND cmake --build ./glfw/build/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GLFW_BUILD_OUTPUT
)
message(STATUS "[Tools] GLFW Build:\n${GLFW_BUILD_OUTPUT}")

execute_process(
    COMMAND copy ./glfw/build/src/Debug/glfw3.lib ./lib/glfw3.lib
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GLFW_COPY
)

message(STATUS "[Tools] GLFW Copy Result:\n${GLFW_COPY}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/include/glm/")

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/" "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(ufbx STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/ufbx.c")
target_include_directories(ufbx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/UFBX/")

add_library(stbi STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp")
target_include_directories(stbi PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/STBI/")

# add_library(glfw INTERFACE)
# target_include_directories(glfw SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/")

# GLFW lib Path: ${CMAKE_SOURCE_DIR}/Tools/third_party/lib/glfw3.lib