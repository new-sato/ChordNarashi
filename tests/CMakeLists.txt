cmake_minimum_required(VERSION 3.10)

add_executable(button_test
    test_button.cpp
)

add_executable(oncebutton_test
    test_oncebutton.cpp
    ../src/oncebutton.cpp
)

target_include_directories(button_test PRIVATE ../src)
target_include_directories(oncebutton_test PRIVATE ../src)

target_link_libraries(button_test PRIVATE gtest)
target_link_libraries(button_test PRIVATE gtest_main)

target_link_libraries(oncebutton_test PRIVATE gtest)
target_link_libraries(oncebutton_test PRIVATE gtest_main)

#調べる
add_test(NAME button COMMAND button_test)
add_test(NAME oncebutton COMMAND oncebutton_test)
