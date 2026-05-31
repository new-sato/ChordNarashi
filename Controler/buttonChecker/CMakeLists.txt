if(ANDROID)
    add_library(
        ButtonChecker STATIC
        src/OnceButton.cpp
        src/IButtonChecker.cpp
        src/SDLButtonChecker.cpp
    )
else()
    add_library(
        ButtonChecker STATIC
        src/OnceButton.cpp
        src/IButtonChecker.cpp
        src/winButtonChecker.cpp
        src/SDLButtonChecker.cpp
    )
endif()

target_include_directories(ButtonChecker PUBLIC ./include)
target_link_libraries(ButtonChecker PUBLIC model_main Display)
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(ButtonChecker PUBLIC SDL3::SDL3)



