cmake_minimum_required(VERSION 4.0)

project(View LANGUAGES CXX)

add_library(View src/View.cpp)

target_link_libraries(View PUBLIC model_main)

find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(View PUBLIC SDL2_ttf::SDL2_ttf-static SDL2::SDL2)
target_include_directories(View PUBLIC ./include)