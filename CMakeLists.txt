cmake_minimum_required(VERSION 3.10)
project(Colossus)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add sub-projects
add_subdirectory(engine)
add_subdirectory(game)