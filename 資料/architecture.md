# ChordNarashi プログラム構造設計メモ (Architecture Reference)

本ドキュメントは、ChordNarashi の MVC（Model-View-Controller）構造、データフロー、およびリファクタリング後の入力システムの全体像をまとめたものです。

---

## 1. 全体構造 (MVC Overview)

ChordNarashi は、ゲーム開発やデスクトップアプリケーション開発で一般的な **MVC (Model-View-Controller)** パターンを忠実に採用しており、各層の関心事が明確に分離されています。

```mermaid
graph TD
    subgraph Controller (制御層)
        Controler[Controlerクラス]
        IButtonChecker[IButtonChecker / SDLButtonChecker]
    end

    subgraph Model (状態・ビジネスロジック層)
        Model[Modelクラス]
        CBM[ChordButtonManager]
        B2C[Button2Chord]
        C2N[Chord2StandardNote]
    end

    subgraph View (表現・出力層)
        View[Viewクラス]
        UI[UI / UIブロック]
        SDLManager[SDLManager / Idisplay]
        MiniaudioNotePlayer[MiniaudioNotePlayer]
    end

    IButtonChecker -- 1. 入力検出 (RealButtons) --> Controler
    Controler -- 2. 状態更新通知 --> Model
    Model -- 3. 描画用データ通知 (Observer) --> View
    View -- 4. 描画・音再生 --> SDLManager & MiniaudioNotePlayer
    SDLManager -- 5. タッチ・マウスクリック検出 --> SDLButtonChecker
```

---

## 2. 各レイヤーの役割

### 2.1. Controller (制御層)
アプリケーションのメインループを管理し、周期的な入力チェックとモデルの更新調整を行います。
* **`Controler`**: `startLoop()` 内でミリ秒単位のメインループを回し、入力のチェック、モデルの更新（キーやコード）、画面の再描画を調整します。
* **`IButtonChecker` (インターフェース)** / **`SDLButtonChecker` (実装)**:
  * キーボード入力（Scancode経由）や、`SDLManager` から取得したマウス/タッチの入力状態を、プラットフォーム共通の `RealButtons` 構造体に変換します。

### 2.2. Model (状態・ビジネスロジック層)
音楽理論的な状態（現在のキー、押されている和音、鳴っている音符）とビジネスロジックを保持します。入力デバイスや画面描画の方法には一切依存しません。
* **`Model`**: Model全体の窓口であり、Controllerからの更新命令を受け取り、各部品に処理を委譲します。
* **`ChordButtonManager`**: 入力された物理ボタン群（`RealButtons`）と現在のキー（五度圏の回転角度）から、音楽的な「仮想和音ボタン（`VirtualChordButton`）」の集合へとマッピングします。
* **`Button2Chord`**: 押されている仮想ボタンの組み合わせ（例：CとAmが同時押しなど）を解釈し、最終的なコードネーム（例：`Am7`）を決定します。
* **`Chord2StandardNote`**: 決定されたコードネームから、実際に鳴らすべき具体的なノート（音階）の配列（周波数/ノート番号）を生成します。
* **`IringButtonTimingManager`**: 即座に音を止めるモードや、スペースキー（サステインペダル）による発音の維持・消音タイミングの制御を担当します。

### 2.3. View (表現・出力層)
Modelの状態を受け取り、画面への描画（五度圏の描画・文字情報の表示）とオーディオ再生を行います。
* **`View`**: `UI` 描画システムとオーディオ再生システム（`MiniaudioNotePlayer`）を統括します。
* **`UI` / `Block` システム**:
  * 画面をいくつかの領域（`Block`）に分割して管理します。
  * `KeyBlock` (現在のキーを表示), `RingingChordBlock` (現在鳴っているコード), `CurrentPressedChordBlock` (準備中のコード), `DisplayCircle` (五度圏サークルの描画)。
  * 各ブロックは、自分の領域内での相対座標（-1.0 〜 1.0）で描画データを構築し、`UI` クラスがウィンドウ全体の実座標へとマッピングして描画します。
* **`SDLManager` (Idisplay実装)**:
  * SDL3を用いたウィンドウ生成、レンダリング、TTFによる文字表示、図形の描画を担当します。
  * **一元化されたイベントポンプ (`pollEvents`)**: OSからのクローズ要求、フォーカス遷移、マウス/タッチ操作等のイベントを一括回収し、安全に各所へ配給します。
* **`MiniaudioNotePlayer`**:
  * ポータブルな音声ライブラリ `miniaudio` を用い、最大同時発音数（16音）のソフトウェアシンセサイザとして、指定された周波数の波形をリアルタイムに合成・出力します。

---

## 3. データ処理パイプライン (Data Pipeline)

物理的なキー押下や画面のタッチが、実際に音になってスピーカーから出力されるまでの流れは以下の通りです。

1. **イベント処理 (SDL)**:
   ユーザーが画面をドラッグ、またはキーを押下。`SDLManager` の `pollEvents()` がイベントを検知し内部状態を更新。
2. **コントローラー更新 (Controller)**:
   `SDLButtonChecker::checkButtons()` が走り、物理キー（Scancode）と画面上のタッチ座標（五度圏上のセクター判定）の両方を統合して `RealButtons` を構築。
3. **キー＆コード決定 (Model)**:
   * キーボタンが押されていた場合、`ChordButtonManager::addKey` で五度圏キー位置をシフト。
   * コードボタンが更新された場合、`ChordButtonManager` が `VirtualChordButton`（Major, minor, dim と Note の組み合わせ）を解決。
   * `Button2Chord` が同時押しロジックに基づき `ChordName`（根音＋コードタイプ）を特定。
4. **発音制御 (Model / Timing)**:
   * Kキーや画面タップの状態に基づき、`IringButtonTimingManager` が「音を鳴らし始めるべきか」「持続すべきか」「止めるべきか」を判定。
   * 鳴らす場合、`Chord2StandardNote` が `ChordName` に基づく音階を配列化し、`NotePlayer` へ通知。
5. **オーディオ出力 (View / audio)**:
   * `MiniaudioNotePlayer` が通知を受け取り、ボイスプールの未使用ボイスに周波数を割り当て。
   * オーディオコールバックが正弦波などを合成してサウンドバッファを駆動し、スピーカーから音が鳴る。

---

## 4. Android移植・モダンUIへの拡張性

* **描画層の抽象化**: すべての描画は `Idisplay`（Character, Rectangle, Circle）を介して行われているため、描画先を Android の GLSurfaceView や他の UI フレームワークに切り替えることが非常に容易です。
* **入力層の抽象化**: 入力はすべて `IButtonChecker` から `RealButtons` にまとめて渡されるため、スマホの加速度センサーや独自のタッチジェスチャーによる演奏を追加する際も、ControllerやModelを改造することなく、新しい `AndroidTouchButtonChecker` を作成するだけで実現できます。
