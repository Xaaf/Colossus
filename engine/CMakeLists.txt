project(Engine)

find_package(glfw3 3.3 REQUIRED)

# Add includes for libraries
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)

# Add our own includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add sources
set(ENGINE_SOURCES
        src/colossus/system/Window.cpp
        src/colossus/Engine.cpp
        src/colossus/input/Keyboard.cpp
        src/colossus/rendering/renderers/OpenGLRenderer.cpp
        src/colossus/rendering/RendererFactory.cpp)
set(ENGINE_HEADERS
        include/colossus/system/logging/Colors.h
        include/colossus/system/logging/Log.h
        include/colossus/system/logging/LogLevels.h
        include/colossus/system/Window.h
        include/colossus/Engine.h
        include/colossus/input/Keyboard.h
        include/colossus/rendering/RendererInterface.h
        include/colossus/rendering/renderers/OpenGLRenderer.h
        include/colossus/rendering/RendererFactory.h)

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

# Link with GLFW
target_link_libraries(engine glfw)