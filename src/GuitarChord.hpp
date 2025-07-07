#pragma once

#include "Chord2Note.hpp"
#include <vector>

class GuitarChord:public Chord2Note
{
    public:
    GuitarChord(Button2Chord& arg):Chord2Note(arg){}
    void generateNote() override;
};
