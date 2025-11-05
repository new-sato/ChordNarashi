add_library(View_sound STATIC
    src/RtMidiNotePlayer.cpp
    src/MIDIMessage.cpp
    src/IMidiNotePlayer.cpp
)

target_link_libraries(View_sound PUBLIC model_main)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(View_sound PUBLIC RtMidi::rtmidi)

target_include_directories(View_sound PUBLIC ./include)