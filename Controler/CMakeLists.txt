add_library(Controler STATIC src/Controler.cpp)

target_include_directories(Controler PUBLIC ./include)
target_link_libraries(Controler PUBLIC View)

