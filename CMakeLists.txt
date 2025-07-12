# 1. CMakeの最小バージョンを指定
cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

# 2. プロジェクトの情報を設定
project(my_project LANGUAGES CXX)

# 3. 使用するC++の標準を指定 (例: C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# 4. 実行ファイルを作成
# add_executable(実行ファイル名 ソースファイル1 ソースファイル2 ...)
add_executable(my_app
    src/main.cpp
    src/allClassManager.cpp
    src/Button2Chord.cpp
    src/ChordButtonManager.cpp
    src/Chord2GuitarNote.cpp
    src/GuitarNotePlayer.cpp
    src/InotePlayer.cpp
    src/keyButtonChecker.cpp
    src/oncebutton.cpp
    src/rightButtonBasic.cpp
    src/sustainPedalManager.cpp
    src/winButtonUpdater.cpp
    # .hファイルはここに記述する必要はありません
)

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE RtMidi::rtmidi)
add_subdirectory(tests)
