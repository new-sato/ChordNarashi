#pragma once

#include "IMidiNotePlayer.hpp"

class View
{
    IMidiNotePlayer& m_midi_note_player;
public:
    View(IMidiNotePlayer& midi_note_player):m_midi_note_player(midi_note_player){};
};