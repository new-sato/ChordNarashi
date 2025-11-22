add_library(MidiPlayer STATIC
    src/RtMidiNotePlayer.cpp
    src/MIDIMessage.cpp
    src/IMidiNotePlayer.cpp
    src/MiniaudioNotePlayer.cpp
)

target_link_libraries(MidiPlayer PUBLIC model_main)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(MidiPlayer PUBLIC RtMidi::rtmidi)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
target_include_directories(MidiPlayer PUBLIC ${MINIAUDIO_INCLUDE_DIRS})

target_include_directories(MidiPlayer PUBLIC ./include)