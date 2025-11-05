#pragma once

#include "InotePlayer.hpp"

/// @brief 受け取ったものを即座に再生する
class StandardNotePlayer:public InotePlayer
{
public:
    StandardNotePlayer() = default;
    /// @brief オブザーバに、再生するべきものを再生するように要請する
    /// @param time 0.0のときのみ、再生開始の処理を行う。
    void playNote(float time) override;
    
    /// @brief オブザーバーに、現在再生しているノートを止めるように依頼する
    void stopNote() override;
    
};