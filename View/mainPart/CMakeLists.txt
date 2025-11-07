add_library(View STATIC src/View.cpp)

target_link_libraries(View PUBLIC model_main)
target_link_libraries(View PUBLIC MidiPlayer)
target_link_libraries(View PUBLIC Display)


target_include_directories(View PUBLIC ./include)
