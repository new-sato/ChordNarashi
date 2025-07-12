#pragma once
#include "InotePlayer.hpp"
#include "Chord2GuitarNote.hpp"
#include <Chrono>

class GuitarNotePlayer:public InotePlayer
{
    RtMidiOut& midiOut;
    
    // MIDIポート繋いだりする
    void init();

    bool do_stroke=false;
    std::chrono::system_clock::time_point prevPlayPoint;
    bool DownStrawk;

    void playNoteStroke(float time);
    void playNoteUpStroke(float time);
    void playNoteDownStroke(float time);
    void playNoteStraight(float time);
    public:
    GuitarNotePlayer(Chord2GuitarNote& c2n, RtMidiOut&);
    GuitarNotePlayer(ChordButtonManager&, RtMidiOut&);
    void playNote(float time) override;
    void stopNote() override;
    void tuggleStroke(){do_stroke=(do_stroke)?false:true;}
};