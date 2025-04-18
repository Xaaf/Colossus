project(Obelisk)

add_library(Obelisk SHARED
    src/ObeliskAPI.cpp
)

target_include_directories(Obelisk
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Obelisk
    PUBLIC OBELISK_EXPORTS
)