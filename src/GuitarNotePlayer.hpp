#pragma once
#include "InotePlayer.hpp"
#include "Chord2GuitarNote.hpp"

class GuitarNotePlayer:public InotePlayer
{
    RtMidiOut midiOut;
    
    // MIDIポート繋いだりする
    void init();
    public:
    GuitarNotePlayer(Chord2GuitarNote& c2n);
    GuitarNotePlayer(ChordButtonManager&);
    void playNote(float time) override;
    void stopNote() override;
};