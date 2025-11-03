#pragma once

#include "Ichord2Note.hpp"
#include <vector>

class Chord2StandardNote:public Ichord2Note
{
    public:
    Chord2StandardNote() = default;

    /// @brief コードネームを受け取り、ノートを生成する。
    /// @param  
    /// @return MIDI番号
    NoteSet generateNote(const ChordName&) override;
};
