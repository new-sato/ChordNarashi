#pragma once
#include "Button2Chord.hpp"
#include <set>

/// @brief MIDIのノートナンバー
using MidiNoteNum = unsigned char;

using NoteSet = std::set<MidiNoteNum>;

class Ichord2Note
{
    
    void notifyRingingChord(const ChordName& arg);
    std::vector<std::function<void(const ChordName&)>> m_ringing_chord_observer;

    protected:
    virtual NoteSet generateNote(const ChordName& arg) = 0;

    public:
    Ichord2Note(){}
    NoteSet processNote(const ChordName& arg);
    void addRingingChordObserver(std::function<void(const ChordName&)>);
};