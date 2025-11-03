cmake_minimum_required(VERSION 4.0)
project(
    toNotePart
    LANGUAGES CXX
    DESCRIPTION "コード鳴らしのモデルの部分を担当"    
)

add_library(toNotePart STATIC
    src/Chord2StandardNote.cpp
)

target_link_libraries(toNotePart PUBLIC toChordNamePart)

target_compile_features(toNotePart PUBLIC cxx_std_17)
target_include_directories(toNotePart PUBLIC ./include)
