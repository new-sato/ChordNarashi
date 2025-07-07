cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(button_test
    test_button.cpp
)

add_executable(oncebutton_test
    test_oncebutton.cpp
    ../src/oncebutton.cpp
)

add_executable(CBM_test
    test_ChordButtonManager.cpp
    ../src/ChordButtonManager.cpp
)

add_executable(Guitar_test
    test_guitarchord.cpp
    ../src/GuitarChord.cpp
    ../src/ChordButtonManager.cpp
    ../src/Button2Chord.cpp
)

target_include_directories(button_test PRIVATE ../src)
target_include_directories(oncebutton_test PRIVATE ../src)
target_include_directories(CBM_test PRIVATE ../src)
target_include_directories(Guitar_test PRIVATE ../src)

target_link_libraries(button_test PRIVATE gtest)
target_link_libraries(button_test PRIVATE gtest_main)

target_link_libraries(oncebutton_test PRIVATE gtest)
target_link_libraries(oncebutton_test PRIVATE gtest_main)

target_link_libraries(CBM_test PRIVATE gtest)
target_link_libraries(CBM_test PRIVATE gtest_main)

target_link_libraries(Guitar_test PRIVATE gtest)
target_link_libraries(Guitar_test PRIVATE gtest_main)

#調べる
add_test(NAME button COMMAND button_test)
add_test(NAME oncebutton COMMAND oncebutton_test)
add_test(NAME cbm COMMAND CBM_test)
add_test(NAME guitar COMMAND Guitar_test)