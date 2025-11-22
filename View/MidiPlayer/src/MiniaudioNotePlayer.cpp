#include "MiniaudioNotePlayer.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <iostream>
#include <cstring>

// 必要に応じて定義
// #define MINIAUDIO_IMPLEMENTATION
// #include "miniaudio.h"

MiniaudioNotePlayer::MiniaudioNotePlayer(Model& model) 
    : IMidiNotePlayer(model) // 基底クラスのコンストラクタを呼ぶ
{
    // ボイスプールの初期化
    m_voices.resize(MAX_POLYPHONY);

    // miniaudioの初期化
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;
    config.playback.channels = 2; // ステレオ
    config.sampleRate        = 48000;
    config.dataCallback      = data_callback;
    config.pUserData         = this; // コールバック内で自分自身にアクセスするため

    if (ma_device_init(NULL, &config, &m_device) == MA_SUCCESS) {
        ma_device_start(&m_device);
        m_isInitialized = true;
    } else {
        std::cerr << "Failed to initialize miniaudio device." << std::endl;
    }
}

MiniaudioNotePlayer::~MiniaudioNotePlayer()
{
    if (m_isInitialized) {
        ma_device_uninit(&m_device);
    }
}

void MiniaudioNotePlayer::updatePlayingNote(const NotePlayInformation& info)
{
    std::lock_guard<std::mutex> lock(m_voiceMutex);

    // 1. 停止するノート (Release)
    for (const auto& note : info.note_to_end) {
        Voice* v = findVoiceByNote(note);
        if (v) {
            v->releasing = true;
        }
    }

    // 2. 新しく鳴らすノート (Attack & Re-trigger)
    for (const auto& note : info.note_to_start) {
        Voice* v = findVoiceByNote(note);

        if (v) {
            // A. 既に鳴っている場合 -> 再トリガー (Re-trigger)
            v->active = true;
            v->releasing = false;       // リリース状態をキャンセル
            // v->phase = 0.0;             // 位相をリセット（アタック感を強調）
            // v->currentVolume = 0.0f;    // 音量を0に戻してから立ち上げる
            // ※もし「ブチッ」という音が気になる場合は currentVolume = 0.0f をコメントアウトしてください
        } 
        else {
            // B. まだ鳴っていない場合 -> 新規割り当て
            v = findFreeVoice();
            if (v) {
                v->active = true;
                v->releasing = false;
                v->noteNumber = note;
                v->frequency = Voice::midiToFreq(note);
                v->phase = 0.0;
                v->currentVolume = 0.0f;
            }
        }
    }

    // 3. 継続するノート (Continue)
    // リリース中だったものがContinueに入っていたら復活させる
    for (const auto& note : info.note_to_continue) {
        Voice* v = findVoiceByNote(note);
        if (v && v->releasing) {
            v->releasing = false; 
        }
    }
}

Voice* MiniaudioNotePlayer::findVoiceByNote(int noteNumber) {
    for (auto& v : m_voices) {
        if (v.active && v.noteNumber == noteNumber) {
            return &v;
        }
    }
    return nullptr;
}

Voice* MiniaudioNotePlayer::findFreeVoice() {
    // 1. 完全な空きボイスを探す
    for (auto& v : m_voices) {
        if (!v.active) return &v;
    }
    
    // 空きがなければ、リリース中のボイスなどを強制的に奪うロジックを入れても良い
    return nullptr; 
}

// オーディオ処理のコールバック（高頻度で呼ばれる）
void MiniaudioNotePlayer::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    MiniaudioNotePlayer* self = (MiniaudioNotePlayer*)pDevice->pUserData;
    float* pOut = (float*)pOutput;
    double sampleRate = (double)pDevice->sampleRate;

    // 出力バッファをゼロクリア
    memset(pOut, 0, sizeof(float) * frameCount * pDevice->playback.channels);

    // データの保護
    // ※注意: オーディオスレッドでのMutexロックは本来避けるべきですが、
    // 簡易実装としてここでは使用します。より高度な実装ではアトミック操作やロックフリーキューを使います。
    std::lock_guard<std::mutex> lock(self->m_voiceMutex);

    for (ma_uint32 i = 0; i < frameCount; ++i) {
        float mixSample = 0.0f;

        // 全ボイスを合成
        for (auto& v : self->m_voices) {
            if (!v.active) continue;

            // --- エンベロープ処理 (簡易ADSR) ---
            const float attackSpeed = 0.001f;  // 立ち上がり速度
            const float releaseSpeed = 0.005f; // 余韻の減衰速度

            if (v.releasing) {
                // リリース中：音量を下げる
                v.currentVolume -= releaseSpeed;
                if (v.currentVolume <= 0.0f) {
                    v.currentVolume = 0.0f;
                    v.active = false; // 完全に消えたら非アクティブ化
                    v.noteNumber = -1;
                }
            } else {
                // アタック/サステイン中：目標音量(0.2くらい)へ向かう
                // 単音量1.0だと和音で割れるので低めに設定
                const float targetVol = 0.1f; 
                if (v.currentVolume < targetVol) {
                    v.currentVolume += attackSpeed;
                    if (v.currentVolume > targetVol) v.currentVolume = targetVol;
                }
            }

            // --- 波形生成 (サイン波) ---
            if (v.active) {
                mixSample += (float)sin(v.phase * 2.0 * 3.14159265) * v.currentVolume;
                mixSample += (float)sin(v.phase* 2 * 2.0 * 3.14159265) * v.currentVolume;

                // 位相を進める
                v.phase += v.frequency / sampleRate;
                if (v.phase > 1.0) v.phase -= 1.0;
            }
        }

        // ステレオ出力 (L/R同じ音)
        pOut[i * 2] = mixSample;     // Left
        pOut[i * 2 + 1] = mixSample; // Right
    }
}