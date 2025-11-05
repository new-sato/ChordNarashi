#pragma once
#include "Button2Chord.hpp"
#include <set>

using MidiNoteNum = unsigned char;
using NoteSet = std::set<MidiNoteNum>;

class Ichord2Note
{
    protected:

    public:
    Ichord2Note(){}
    virtual NoteSet generateNote(const ChordName& arg) = 0;
};