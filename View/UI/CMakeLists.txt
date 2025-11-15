add_library(UI STATIC
    src/UI.cpp
    src/Block.cpp
)

target_include_directories(UI PUBLIC ./include)
target_link_libraries(UI PUBLIC Display)
target_link_libraries(UI PUBLIC model_main)

