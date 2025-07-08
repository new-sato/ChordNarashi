#pragma once
#include "InotePlayer.hpp"
#include "GuitarChord.hpp"

class GuitarNotePlayer:public InotePlayer
{
    RtMidiOut midiOut;
    
    // MIDIポート繋いだりする
    void init();
    public:
    GuitarNotePlayer(GuitarChord& c2n);
    GuitarNotePlayer(ChordButtonManager&);
    void playNote(float time) override;
    void stopNote() override;
};