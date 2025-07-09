#pragma once

#include "Chord2Note.hpp"
#include <vector>

class Chord2GuitarNote:public Chord2Note
{
    public:
    Chord2GuitarNote(Button2Chord& arg):Chord2Note(arg){}
    Chord2GuitarNote(ChordButtonManager& cbm):Chord2Note(cbm){}
    void generateNote() override;
};
