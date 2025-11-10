add_library(ringButtonTimingManager STATIC
    src/IringButtonTimingManager.cpp
    src/noSustainTimingManager.cpp
)

target_include_directories(ringButtonTimingManager PUBLIC ./include)
