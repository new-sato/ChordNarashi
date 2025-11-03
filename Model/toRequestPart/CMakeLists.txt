cmake_minimum_required(VERSION 4.0)
project(
    toRequestPart
    LANGUAGES CXX
    DESCRIPTION "再生のリクエストを送るところまで"
)

add_library(toRequestPart
    src/StandardNotePlayer.cpp
)

target_link_libraries(toRequestPart PUBLIC toNotePart)

target_compile_features(toRequestPart PUBLIC cxx_std_17)
target_include_directories(toRequestPart PUBLIC ./include)
