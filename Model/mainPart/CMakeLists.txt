add_library(
    model_main
    src/Model.cpp
)

target_link_libraries(model_main PUBLIC toRequestPart)

target_compile_features(model_main PUBLIC cxx_std_17)
target_include_directories(model_main PUBLIC ./include)
