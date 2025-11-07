add_library(Ui STATIC src/SDLManager.cpp)

target_include_directories(Ui PUBLIC ./include)
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(Ui PRIVATE SDL3::SDL3)