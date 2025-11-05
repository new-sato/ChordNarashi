#pragma once


#include "IMidiNotePlayer.hpp"

#include <rtmidi/RtMidi.h>

class RtMidiNotePlayer:public IMidiNotePlayer
{
    RtMidiOut midiOut;
    
    // MIDIポート繋いだりする
    void init();

    public:
    RtMidiNotePlayer(Model&);
    void updatePlayingNote(const NotePlayInformation&) override;
};