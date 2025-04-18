project(Colossus)

add_executable(Colossus
    src/main.cpp
)

target_link_libraries(Colossus
    PRIVATE Obelisk
)

target_include_directories(Colossus
    PRIVATE ${CMAKE_SOURCE_DIR}/Engine/include
)