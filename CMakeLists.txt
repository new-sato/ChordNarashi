# 1. CMakeの最小バージョンを指定
cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

# 2. プロジェクトの情報を設定
project(my_project LANGUAGES CXX)

# 3. 使用するC++の標準を指定 (例: C++17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 4. サブディレクトリを追加
add_subdirectory(./Model)
add_subdirectory(./View)
add_subdirectory(./Controler)

# 5. 実行ファイルまたは共有ライブラリを作成
if(ANDROID)
    add_library(main SHARED
        src/main.cpp
    )
    target_link_libraries(main PRIVATE Controler)

    # Android needs these linked to the main library
    find_package(SDL3 CONFIG REQUIRED)
    find_package(SDL3_ttf CONFIG REQUIRED)
    target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)
else()
    add_executable(my_app
        src/main.cpp
    )
    target_link_libraries(my_app PRIVATE Controler)
endif()

if(ANDROID)
    # vcpkgが生成した.soファイルを、Androidのパッケージ（APK）に含めるための設定
    # main ターゲットが依存している SDL3 などの共有ライブラリを自動追従させます
    set_target_properties(main PROPERTIES
            BUNDLE_EXTENSION "so"
    )
endif()
