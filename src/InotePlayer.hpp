#pragma once
#include "Chord2Note.hpp"

#include "rtmidi/RtMidi.h"

/// @brief ボタンから受け取った情報を基に、決められたノートの再生を行う
class InotePlayer
{
    protected:
    Chord2Note& chord_2_note;
    note_set note_to_play;
    public:
    InotePlayer(Chord2Note& c2n);
    virtual void updateNote();
    virtual void playNote(float time) = 0;
    virtual void stopNote() = 0;
};