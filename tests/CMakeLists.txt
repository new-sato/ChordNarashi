cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(button_test
    test_button.cpp
)

add_executable(oncebutton_test
    test_oncebutton.cpp
    ../src/oncebutton.cpp
)

add_executable(winButton_test
    test_winButton.cpp
    ../src/oncebutton.cpp
    ../src/winButtonUpdater.cpp
)

add_executable(CBM_test
    test_ChordButtonManager.cpp
    ../src/keyButtonChecker.cpp
    ../src/ChordButtonManager.cpp
    ../src/oncebutton.cpp
)

add_executable(Guitar_test
    test_guitarchord.cpp
    ../src/GuitarChord.cpp
    ../src/ChordButtonManager.cpp
    ../src/keyButtonChecker.cpp
    ../src/oncebutton.cpp
    ../src/Button2Chord.cpp
)

add_executable(GuitarNote_test
    test_GuitarNotePlayer.cpp
    ../src/GuitarNotePlayer.cpp
    ../src/InotePlayer.cpp
    ../src/GuitarChord.cpp
    ../src/ChordButtonManager.cpp
    ../src/keyButtonChecker.cpp
    ../src/oncebutton.cpp
    ../src/Button2Chord.cpp
)

target_include_directories(button_test PRIVATE ../src)
target_include_directories(oncebutton_test PRIVATE ../src)
target_include_directories(winButton_test PRIVATE ../src)
target_include_directories(CBM_test PRIVATE ../src)
target_include_directories(Guitar_test PRIVATE ../src)
target_include_directories(GuitarNote_test PRIVATE ../src)

target_link_libraries(button_test PRIVATE gtest)
target_link_libraries(button_test PRIVATE gtest_main)

target_link_libraries(winButton_test PRIVATE gtest)
target_link_libraries(winButton_test PRIVATE gtest_main)

target_link_libraries(oncebutton_test PRIVATE gtest)
target_link_libraries(oncebutton_test PRIVATE gtest_main)

target_link_libraries(CBM_test PRIVATE gtest)
target_link_libraries(CBM_test PRIVATE gtest_main)

target_link_libraries(Guitar_test PRIVATE gtest)
target_link_libraries(Guitar_test PRIVATE gtest_main)

target_link_libraries(GuitarNote_test PRIVATE gtest)
target_link_libraries(GuitarNote_test PRIVATE gtest_main)

#調べる
add_test(NAME button COMMAND button_test)
add_test(NAME oncebutton COMMAND oncebutton_test)
add_test(NAME winButton COMMAND winButton_test)
add_test(NAME cbm COMMAND CBM_test)
add_test(NAME guitar COMMAND Guitar_test)
add_test(NAME player COMMAND GuitarNote_test)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(Guitar_test PRIVATE RtMidi::rtmidi)
target_link_libraries(GuitarNote_test PRIVATE RtMidi::rtmidi)