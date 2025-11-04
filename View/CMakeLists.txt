add_library(View src/View.cpp)

target_link_libraries(View PUBLIC model_main)

find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(View PUBLIC SDL2_ttf::SDL2_ttf-static SDL2::SDL2)

find_package(rtmidi CONFIG REQUIRED)

target_include_directories(View PUBLIC ./include)

add_subdirectory(sound)