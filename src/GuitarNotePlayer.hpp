#pragma once
#include "InotePlayer.hpp"
#include "GuitarChord.hpp"

class GuitarNotePlayer:public InotePlayer
{
    RtMidiOut midiOut;

    public:
    GuitarNotePlayer(GuitarChord& c2n);
};