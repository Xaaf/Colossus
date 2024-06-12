project(Engine)

find_package(glfw3 3.3 REQUIRED)

# Add includes for libraries
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)

# Add our own includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add sources
set(ENGINE_SOURCES
        src/Colossus/Engine.cpp
        src/Colossus/Input/Keyboard.cpp
        src/Colossus/Render/Renderers/OpenGLRenderer.cpp
        src/Colossus/Render/RendererFactory.cpp
        src/Colossus/Render/Window.cpp)
set(ENGINE_HEADERS
        include/Colossus/System/Logging/Colors.h
        include/Colossus/System/Logging/Log.h
        include/Colossus/System/Logging/LogLevels.h
        include/Colossus/Engine.h
        include/Colossus/Input/Keyboard.h
        include/Colossus/Render/RendererInterface.h
        include/Colossus/Render/Renderers/OpenGLRenderer.h
        include/Colossus/Render/RendererFactory.h
        include/Colossus/Render/Window.h)

# Add glad source
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c
        include/Colossus/Input/InputCodes.h)

# Add precompiled header sources
set(PCH_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/cspch.h)
set(PCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/cspch.cpp)

# Create precompiled header target
add_library(pch STATIC ${PCH_SOURCE})
target_compile_features(pch PUBLIC cxx_std_17)
target_precompile_headers(pch PUBLIC ${PCH_HEADER})

# Create static library
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

# Link with GLFW
target_link_libraries(engine glfw)