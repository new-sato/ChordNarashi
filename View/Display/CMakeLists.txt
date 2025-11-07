add_library(Display STATIC src/SDLManager.cpp)

target_include_directories(Display PUBLIC ./include)
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(Display PRIVATE SDL3::SDL3)