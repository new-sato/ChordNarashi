if(ANDROID)
    add_library(MidiPlayer STATIC
        src/MIDIMessage.cpp
        src/IMidiNotePlayer.cpp
        src/MiniaudioNotePlayer.cpp
    )
else()
    add_library(MidiPlayer STATIC
        src/RtMidiNotePlayer.cpp
        src/MIDIMessage.cpp
        src/IMidiNotePlayer.cpp
        src/MiniaudioNotePlayer.cpp
    )
endif()

target_link_libraries(MidiPlayer PUBLIC model_main)

if(NOT ANDROID)
    find_package(rtmidi CONFIG REQUIRED)
    target_link_libraries(MidiPlayer PUBLIC RtMidi::rtmidi)
endif()

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")
target_include_directories(MidiPlayer PUBLIC ${MINIAUDIO_INCLUDE_DIRS})

target_include_directories(MidiPlayer PUBLIC ./include)