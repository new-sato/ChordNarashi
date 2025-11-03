#pragma once
#include "Button2Chord.hpp"
#include <set>

using NoteSet = std::set<int>;

class Ichord2Note
{
    protected:

    public:
    Ichord2Note(){}
    virtual NoteSet generateNote(const ChordName& arg) = 0;
};