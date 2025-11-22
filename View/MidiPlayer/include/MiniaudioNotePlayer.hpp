#pragma once

#include "IMidiNotePlayer.hpp"
#include "miniaudio.h" // miniaudio.hの実体はcpp側で定義するか、プロジェクト設定に従ってください
#include <vector>
#include <mutex>
#include <atomic>
#include <cmath>

// 1つの音（ボイス）を管理する構造体
struct Voice {
    int noteNumber = -1;    // 現在担当しているMIDIノート番号 (-1は未使用)
    bool active = false;    // 発音中かどうか
    bool releasing = false; // リリース（減衰）フェーズかどうか
    double phase = 0.0;     // 現在の波形の位相
    float currentVolume = 0.0f; // 現在の音量（エンベロープ用）
    double frequency = 0.0;     // 周波数

    // MIDIノート番号から周波数を計算
    static double midiToFreq(int note) {
        return 440.0 * std::pow(2.0, (note - 69) / 12.0);
    }
};

class MiniaudioNotePlayer : public IMidiNotePlayer
{
private:
    ma_device m_device;
    bool m_isInitialized = false;

    // 同時発音数（ポリフォニー）の上限
    static const int MAX_POLYPHONY = 16;
    
    // ボイスのプール
    std::vector<Voice> m_voices;

    // スレッド間でのデータ競合を防ぐためのミューテックス
    std::mutex m_voiceMutex;

    // miniaudioからのコールバック
    static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

public:
    // コンストラクタ
    MiniaudioNotePlayer(Model& model);
    
    // デストラクタ
    ~MiniaudioNotePlayer();

    // IMidiNotePlayerからのオーバーライド
    // NotePlayInformationを受け取り、発音状態を更新する
    void updatePlayingNote(const NotePlayInformation& info) override;

private:
    // 内部ヘルパー: 指定したノート番号を鳴らしているボイスを探す
    Voice* findVoiceByNote(int noteNumber);
    
    // 内部ヘルパー: 未使用のボイスを探す
    Voice* findFreeVoice();
};