add_library(View STATIC src/View.cpp)

target_link_libraries(View PUBLIC model_main)
target_link_libraries(View PUBLIC View_sound)


target_include_directories(View PUBLIC ./include)
