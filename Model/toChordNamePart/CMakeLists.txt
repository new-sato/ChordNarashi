add_library(toChordNamePart STATIC
    src/VirtualChordButtons.cpp
    src/Button2Chord.cpp
    src/ChordButtonManager.cpp
)

target_compile_features(toChordNamePart PUBLIC cxx_std_17)
target_include_directories(toChordNamePart PUBLIC ./include)
