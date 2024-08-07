project(Engine)

find_package(OpenGL REQUIRED)

# Add includes
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add GLFW include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw/include)
# Add GLM include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm)

# Add STB include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/stb/include)


# Set GLFW build flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Lib Only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW Lib Only")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/build/glfw)

# Add sources
set(ENGINE_SOURCES
        src/Colossus/Engine.cpp
        src/Colossus/Input/Keyboard.cpp
        src/Colossus/Render/Arch/OpenGL/OpenGLRenderer.cpp
        src/Colossus/Render/Renderer.cpp
        src/Colossus/Render/Window.cpp
        src/Colossus/Render/Arch/OpenGL/Shader.cpp
        src/Colossus/Render/Arch/OpenGL/Texture.cpp
        src/Colossus/Render/Mesh.cpp
        src/Colossus/Transform.cpp)
set(ENGINE_HEADERS
        include/Colossus/System/Logging/Colors.h
        include/Colossus/System/Logging/Log.h
        include/Colossus/System/Logging/LogLevels.h
        include/Colossus/Engine.h
        include/Colossus/Input/Keyboard.h
        include/Colossus/Input/InputCodes.h
        include/Colossus/Render/RendererInterface.h
        include/Colossus/Render/Arch/OpenGL/OpenGLRenderer.h
        include/Colossus/Render/Renderer.h
        include/Colossus/Render/Window.h
        include/Colossus/Render/Arch/OpenGL/Shader.h
        include/Colossus/Render/Arch/OpenGL/Texture.h
        include/Colossus/Render/Mesh.h
        include/Colossus/Transform.h
        include/Colossus/Objects/Entity.h
)

# Add glad source
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c)

# Add precompiled header sources
set(PCH_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/cspch.h)
set(PCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/cspch.cpp)

# Create precompiled header target
add_library(pch STATIC ${PCH_SOURCE})
target_compile_features(pch PUBLIC cxx_std_17)
target_precompile_headers(pch PUBLIC ${PCH_HEADER})

# Create static library
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

# Link with GLFW and OpenGL
target_link_libraries(engine ${OPENGL_LIBRARIES} glfw)
