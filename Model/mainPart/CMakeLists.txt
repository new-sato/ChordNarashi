cmake_minimum_required(VERSION 4.0)

project(
    model_main
    LANGUAGES CXX
    DESCRIPTION "Modelの中核部"
)

add_library(
    model_main
    src/Model.cpp
)

target_link_libraries(model_main PUBLIC toRequestPart)

target_compile_features(model_main PUBLIC cxx_std_17)
target_include_directories(model_main PUBLIC ./include)
