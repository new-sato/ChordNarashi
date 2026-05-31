# Androidビルド手順書

本プロジェクト（ChordNarashi）を Android 向けにビルドするための手順をまとめます。

## 1. 準備

### 必要な環境
- **Android SDK / NDK**: Android Studio 経由でインストール。
- **vcpkg**: 依存ライブラリ（SDL3, miniaudio等）の管理。
- **Java (JDK)**: ビルドスクリプトの実行に必要。

### 環境変数の設定
ビルドを行うターミナル（PowerShell等）で、以下の環境変数が正しく設定されている必要があります。
- `ANDROID_HOME`: Android SDK のルートディレクトリ
- `ANDROID_NDK_HOME`: 使用する NDK のバージョンディレクトリ

## 2. ビルドコマンド

プロジェクトのルートディレクトリから以下のコマンドを実行します。

```powershell
# 1. Androidプロジェクトディレクトリに移動
cd android-project

# 2. 環境変数を一時的に設定（設定済みでない場合）
$env:ANDROID_HOME = "C:/Users/satou/AppData/Local/Android/Sdk"
$env:ANDROID_NDK_HOME = "C:/Users/satou/AppData/Local/Android/Sdk/ndk/30.0.14904198"

# 3. Gradleを使用してビルド実行
./gradlew assembleDebug
```

## 3. 生成物

ビルドが成功すると、以下のパスに APK ファイルが生成されます。

`android-project/app/build/outputs/apk/debug/app-debug.apk`

これを Android 端末に転送してインストールすることで、アプリを実行できます。

## 4. トラブルシューティング

### 共有ライブラリ (.so) が見つからない
もし `libSDL3.so not found` などのエラーが出る場合は、以下の点を確認してください。
- `android-triplet.cmake` で `VCPKG_LIBRARY_LINKAGE` が `static` に設定されているか。
- `build.gradle` で `VCPKG_CHAINLOAD_TOOLCHAIN_FILE` や `VCPKG_TARGET_TRIPLET` が正しく渡されているか。

### キャッシュのクリア
ビルド設定を大きく変更した後は、`.cxx` ディレクトリや `app/build` ディレクトリを削除してから再ビルドすることをお勧めします。
```powershell
Remove-Item -Recurse -Force app/.cxx
Remove-Item -Recurse -Force app/build
```
