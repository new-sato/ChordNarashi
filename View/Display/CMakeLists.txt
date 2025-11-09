add_library(Display STATIC
    src/SDLManager.cpp
    src/SDLTextureData.cpp
    src/SDLCharacterManager.cpp
)

target_include_directories(Display PUBLIC ./include)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
target_link_libraries(Display PRIVATE SDL3::SDL3)
target_link_libraries(Display PRIVATE $<IF:$<TARGET_EXISTS:SDL3_ttf::SDL3_ttf>,SDL3_ttf::SDL3_ttf,SDL3_ttf::SDL3_ttf-static>)