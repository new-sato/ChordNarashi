cmake_minimum_required(VERSION 3.10)

add_executable(button_test
    test_button.cpp
)

target_include_directories(button_test PRIVATE ../src)

target_link_libraries(button_test PRIVATE gtest)
target_link_libraries(button_test PRIVATE gtest_main)


#調べる
add_test(NAME button COMMAND button_test)

