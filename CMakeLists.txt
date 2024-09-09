cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AdventureConsoleGame")

add_executable (AdventureConsoleGame "main.c" "room/room.c" "room/room.h" "player/player.c" "player/player.h" "game/game.h" "game/game.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventureConsoleGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
