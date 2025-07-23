project(Obelisk)

# Require OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Add GLFW as a subdirectory (this prevents out-of-tree source errors)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Lib Only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW Lib Only")

set(PCH_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/ObeliskPCH.h)
set(PCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/ObeliskPCH.cpp)

# Add static library for the PCH
add_library(pch STATIC ${PCH_SOURCE})
target_compile_features(pch PUBLIC cxx_std_20)
target_precompile_headers(pch PUBLIC ${PCH_HEADER})

# Add include directories to PCH target
target_include_directories(pch
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/GLFW/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/external/GLM
        ${CMAKE_SOURCE_DIR}/external/stb/include
)

# Specify the binary directory for building GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/external/GLFW ${CMAKE_BINARY_DIR}/external/glfw)

# Create the Obelisk engine library
add_library(Obelisk SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c

        src/ObeliskAPI.cpp
        src/ObeliskPCH.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Renderer/Window.cpp
        src/Scene/Entity.cpp
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
        ${CMAKE_SOURCE_DIR}/external/GLM
        ${CMAKE_SOURCE_DIR}/external/stb/include
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