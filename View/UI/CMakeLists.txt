add_library(UI STATIC
    src/UI.cpp
    src/Block.cpp
    src/KeyBlock.cpp
    src/RingingChordBlock.cpp
    src/DisplayCircleBlock.cpp
    src/CurrentPressedChordBlock.cpp
)

target_include_directories(UI PUBLIC ./include)
target_link_libraries(UI PUBLIC Display)
target_link_libraries(UI PRIVATE model_main)

