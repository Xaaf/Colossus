cmake_minimum_required(VERSION 3.16)
project(Colossus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(Engine)
add_subdirectory(GameClient)

set_target_properties(Obelisk PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(Colossus PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

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

# Doxygen documentation target
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    
    message(STATUS "Doxygen found. Use 'make docs' or 'cmake --build . --target docs' to generate documentation.")
else()
    message(WARNING "Doxygen not found. Documentation target will not be available.")
endif()