#include "Chord2Note.hpp"

#include "rtmidi/RtMidi.h"

/// @brief ボタンから受け取った情報を基に、決められたノートの再生を行う
class InotePlayer
{
    Chord2Note& chord_2_note;
    public:
    InotePlayer(Chord2Note& c2n);
    virtual void playNote() = 0;
    
};