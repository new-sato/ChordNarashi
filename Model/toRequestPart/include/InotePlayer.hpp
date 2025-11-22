#pragma once
#include "Ichord2Note.hpp"

#include <functional>

struct NotePlayInformation
{
    /// @brief これから再生処理を行う（まだ再生していない）ノート
    const NoteSet note_to_start;

    /// @brief 再生を開始する処理は終えており、継続して鳴らし続けるノート
    const NoteSet note_to_continue;

    /// @brief これから停止処理を行うノート
    const NoteSet note_to_end;

    NotePlayInformation(NoteSet s, NoteSet c, NoteSet e)
    :note_to_start(s), note_to_continue(c), note_to_end(e){}
};

/// @brief 受け取った情報を基に、決められたノートの再生をView層に依頼する。アルペジエーター的機能もこいつが担う
class InotePlayer
{
    protected:
    /// @brief これから再生開始の処理を行うべきノート
    NoteSet m_note_to_play = {};
    
    /// @brief すでに再生開始処理を行ったノート
    NoteSet m_note_played = {};

    /// @brief ノートの再生を通知する相手
    std::vector<std::function<void(const NotePlayInformation&)>> m_PlayObservers;
    void notifyPlaying(const NotePlayInformation&);

    public:
    InotePlayer() = default;
    virtual void updateNote(const NoteSet& note_to_play){m_note_to_play = note_to_play;};
    virtual void playNote(float time) = 0;
    virtual void stopNote() = 0;
    
    void addPlayObserver(std::function<void(const NotePlayInformation&)> arg);
};