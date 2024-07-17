# Tools CMake

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/")

add_library(data_types STATIC "${CMAKE_CURRENT_SOURCE_DIR}/data_types/data_types.c")
target_include_directories(data_types PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/data_types/include/")

add_library(data_struct STATIC "${CMAKE_CURRENT_SOURCE_DIR}/data_struct/data_struct.c")
target_include_directories(data_struct PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/data_struct/include/")
target_link_libraries(data_struct data_types)

add_library(roots_math STATIC "${CMAKE_CURRENT_SOURCE_DIR}/roots_math/roots_math.c")
target_include_directories(roots_math PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/roots_math/include/")

add_library(asset_io STATIC "${CMAKE_CURRENT_SOURCE_DIR}/asset_io/asset_io.c")
target_include_directories(asset_io PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/asset_io/include/")
target_link_libraries(asset_io stbi ufbx data_struct)