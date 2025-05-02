cmake_minimum_required(VERSION 3.16)
project(Colossus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(Engine)
add_subdirectory(GameClient)

# Add assets folder (shaders)
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*")
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILENAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${CMAKE_BINARY_DIR}/assets/shaders/${FILENAME} COPYONLY)
endforeach()

# Add assets folder (textures)
file(GLOB TEXTURE_FILES "${CMAKE_SOURCE_DIR}/assets/textures/*")
foreach(TEXTURE_FILE ${TEXTURE_FILES})
    get_filename_component(FILENAME ${TEXTURE_FILE} NAME)
    configure_file(${TEXTURE_FILE} ${CMAKE_BINARY_DIR}/assets/textures/${FILENAME} COPYONLY)
endforeach()
