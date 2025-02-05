# RootsEngine CMake
message("[Frontend]")
add_library(console STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Console/Console.cpp")
target_include_directories(console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Console/include/")

add_library(entity INTERFACE)
target_include_directories(entity INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/Entity/include/")

add_library(item STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Item/Item.cpp")
target_include_directories(item PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Item/include/")
target_link_libraries(item entity)

add_library(npc STATIC "${CMAKE_CURRENT_SOURCE_DIR}/NPC/NPC.cpp")
target_include_directories(npc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/NPC/include/")
target_link_libraries(npc entity item)

add_library(game_world STATIC "${CMAKE_CURRENT_SOURCE_DIR}/GameWorld/GameWorld.cpp")
target_include_directories(game_world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GameWorld/include/")
target_link_libraries(game_world npc item)


add_executable(frontend "${CMAKE_CURRENT_SOURCE_DIR}/frontend_main.cpp")
target_link_libraries(frontend console game_world)
