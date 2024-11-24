# Testing CMake

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/")
add_executable(testing_main "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")
target_link_libraries(testing_main glad glfw asset_io data_struct roots_math)