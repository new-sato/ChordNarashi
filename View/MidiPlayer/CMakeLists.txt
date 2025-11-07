add_library(MidiPlayer STATIC
    src/RtMidiNotePlayer.cpp
    src/MIDIMessage.cpp
    src/IMidiNotePlayer.cpp
)

target_link_libraries(MidiPlayer PUBLIC model_main)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(MidiPlayer PUBLIC RtMidi::rtmidi)

target_include_directories(MidiPlayer PUBLIC ./include)