# Testing CMake

add_executable(testing_main "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")
target_link_libraries(testing_main glfw data_types)