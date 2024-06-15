cmake_minimum_required(VERSION 3.10)
project(Colossus)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add sub-projects
add_subdirectory(engine)
add_subdirectory(game)

# Add assets folder
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*")
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILENAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${CMAKE_BINARY_DIR}/game/assets/shaders/${FILENAME} COPYONLY)
endforeach()
file(GLOB TEXTURE_FILES "${CMAKE_SOURCE_DIR}/assets/textures/*")
foreach(TEXTURE_FILE ${TEXTURE_FILES})
    get_filename_component(FILENAME ${TEXTURE_FILE} NAME)
    configure_file(${TEXTURE_FILE} ${CMAKE_BINARY_DIR}/game/assets/textures/${FILENAME} COPYONLY)
endforeach()