add_library(UIimpliment STATIC
    src/KeyBlock.cpp
    src/RingingChordBlock.cpp
    src/DisplayCircleBlock.cpp
    src/CurrentPressedChordBlock.cpp
)

target_include_directories(UIimpliment PUBLIC ./include)
target_link_libraries(UIimpliment PUBLIC UI)