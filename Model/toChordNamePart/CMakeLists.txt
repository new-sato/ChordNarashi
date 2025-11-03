cmake_minimum_required(VERSION 4.0)
project(
    toChordNamePart
    LANGUAGES CXX
    DESCRIPTION "コード鳴らしのモデルの部分を担当"    
)

add_library(toChordNamePart STATIC
    src/Button2Chord.cpp
    src/ChordButtonManager.cpp
)

target_compile_features(toChordNamePart PUBLIC cxx_std_17)
target_include_directories(toChordNamePart PUBLIC ./include)
