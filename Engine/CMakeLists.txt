project(Obelisk)

# Require OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Add GLFW as a subdirectory (this prevents out-of-tree source errors)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Lib Only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW Lib Only")

# Specify the binary directory for building GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/external/GLFW ${CMAKE_BINARY_DIR}/external/glfw)

# Create the Obelisk engine library
add_library(Obelisk SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c

        src/ObeliskAPI.cpp
)

# Tell CMake to not use the PCH for glad.c
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

# Link dependencies
target_link_libraries(Obelisk PRIVATE glfw ${OPEN_GL_LIBRARIES})

# Include paths
target_include_directories(Obelisk
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/GLFW/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
)

# Set PCH
target_precompile_headers(Obelisk
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Obelisk/ObeliskPCH.hpp
)

# Ensure using CPP for the PCH
set_target_properties(Obelisk PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
)

target_compile_definitions(Obelisk
        PUBLIC OBELISK_EXPORTS
)