#pragma once

#include "Ichord2Note.hpp"
#include <vector>

class Chord2StandardNote:public Ichord2Note
{
    public:
    Chord2StandardNote() = default;
    NoteSet generateNote(const ChordName&) override;
};
