add_library(
    ButtonChecker STATIC 
    src/OnceButton.cpp
    src/IButtonChecker.cpp
    src/winButtonChecker.cpp
)

target_include_directories(ButtonChecker PUBLIC ./include)
target_link_libraries(ButtonChecker PUBLIC model_main)

