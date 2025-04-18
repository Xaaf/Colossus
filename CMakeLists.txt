cmake_minimum_required(VERSION 3.16)
project(Colossus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(Engine)
add_subdirectory(GameClient)