add_library(toRequestPart
    src/InotePlayer.cpp
    src/StandardNotePlayer.cpp
)

target_link_libraries(toRequestPart PUBLIC toNotePart)

target_compile_features(toRequestPart PUBLIC cxx_std_17)
target_include_directories(toRequestPart PUBLIC ./include)
