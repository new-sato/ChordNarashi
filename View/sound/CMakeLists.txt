cmake_minimum_required(VERSION 4.0)

add_library(View_sound src/RtMidiNotePlayer.cpp)

target_link_libraries(View_sound PUBLIC model_main)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(View_sound PRIVATE RtMidi::rtmidi)

target_include_directories(View_sound PUBLIC ./include)