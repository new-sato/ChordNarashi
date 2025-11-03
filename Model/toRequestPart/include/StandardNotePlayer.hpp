#pragma once

#include "InotePlayer.hpp"

/// @brief 受け取ったものを即座に再生する
class StandardNotePlayer:public InotePlayer
{
public:
    StandardNotePlayer() = default;
    void playNote(float time) override;
    void stopNote() override;

    
};