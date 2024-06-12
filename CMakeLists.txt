cmake_minimum_required(VERSION 3.10)
project(Colossus)

set(GLFW3_DIR "/usr/local/lib/cmake/glfw3" CACHE PATH "Path to GLFW3Config.cmake")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add sub-projects
add_subdirectory(engine)
add_subdirectory(game)