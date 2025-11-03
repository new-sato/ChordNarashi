#pragma once

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

class Model
{
    ChordButtonManager chord_button_manager;
    Button2Chord button_to_chord;
    Chord2StandardNote chord_to_standard_note;
    StandardNotePlayer standard_note_player;

public:
    Model();
};
