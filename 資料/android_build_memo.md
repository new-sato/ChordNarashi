# Androidビルド構築メモ (ChordNarashi)

本プロジェクトを Windows 環境から Android 向けにビルド可能にするために行った工夫と修正の記録です。

---

## 1. ビルドディレクトリの分離
Windows 用のビルド成果物（`build/`）と衝突しないよう、Android 用には個別のディレクトリ管理が必要です。
- **Android Studio経由**: 自動的に `app/.cxx` 内でビルドされるため衝突しません。
- **CLI経由**: `.build-android/` のような別ディレクトリを作成し、`.gitignore` に追加しました。

---

## 2. 依存ライブラリの管理 (vcpkg)
最も難易度が高かったのは Android 向けライブラリのクロスコンパイル設定です。

### カスタム Triplet (`android-triplet.cmake`)
vcpkg 標準の `arm64-android` ではなく、プロジェクトルートに独自の Triplet ファイルを作成しました。
- **工夫点**: `VCPKG_CHAINLOAD_TOOLCHAIN_FILE` を使用し、Android NDK 付属の CMake ツールチェーンを vcpkg 内部で呼び出すように設定。
- **ABI設定**: `arm64-v8a` を明示。

### `vcpkg.json` のプラットフォーム制限
一部のライブラリ（`rtmidi` など）は Android 環境でそのままビルドできない、あるいは不要なため、条件付き依存関係に設定しました。
```json
{
  "name": "rtmidi",
  "platform": "!android"
}
```

---

## 3. CMake のクロスプラットフォーム対応
一つの `CMakeLists.txt` で Windows と Android 両方に対応させるための修正を行いました。

### 成果物形式の切り替え
Android では `main` という名前の **共有ライブラリ (.so)** が必要です。
```cmake
if(ANDROID)
    add_library(main SHARED src/main.cpp)
else()
    add_executable(my_app src/main.cpp)
endif()
```

### プラットフォーム固有コードの除外
Windows API (`windows.h`) に依存するコード（`winButtonChecker.cpp`）などが Android ビルドに含まれないよう、CMake で条件分岐を追加しました。

---

## 4. Gradle と CMake の連携
`android-project/app/build.gradle` で、Android Studio が vcpkg を認識できるように設定しました。

- **パスの正規化**: Windows のバックスラッシュ (`\`) は CMake 内でエスケープ文字と誤認されるため、`.replace('\\', '/')` でスラッシュに統一。
- **VCPKG_OVERLAY_TRIPLETS**: プロジェクト直下に置いたカスタム Triplet を読み込むためのパス指定。
- **VCPKG_MANIFEST_DIR**: `vcpkg.json` がある場所を明示的に指定。

---

## 5. アセット (Assets) の扱い
SDL3 は Android の `assets` フォルダ内のファイルを相対パスで読み込めます。
- `View/Display/assets/` -> `android-project/app/src/main/assets/assets/` へコピー。
- コード側では `assets/GenShinGothic-Regular.ttf` として共通のパスでアクセス可能です。

---

## 6. トラブルシューティングのポイント
- **NDK Version**: `build.gradle` の `ndkVersion` と、実際にインストールされているフォルダ名（`30.0.14904198` など）を完全に一致させる必要があります。
- **C++20**: Android NDK の Clang でも C++20 を使用するため、`set(CMAKE_CXX_STANDARD 20)` を維持し、NDK 側で対応する API レベル（API 24 以上）を設定しました。
