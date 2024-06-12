# GameLogic/CMakeLists.txt

project(Game)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/engine/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)

# Add sources
set(GAME_SOURCES
        src/game/GameLogic.cpp
        src/Main.cpp)
set(GAME_HEADERS
        include/game/GameLogic.h)

set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c)

# Create the game executable
add_executable(game ${GAME_SOURCES} ${GAME_HEADERS} ${GLAD_SOURCE})

# Link the engine with the game
target_link_libraries(game engine)
