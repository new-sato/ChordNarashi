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
    # .hファイルはここに記述する必要はありません
)

add_subdirectory(tests)
