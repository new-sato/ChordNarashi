#pragma once

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include <chrono>
#include <memory>

class Model
{
    ChordButtonManager chord_button_manager;
    Button2Chord button_to_chord;
    std::unique_ptr<Ichord2Note> chord_to_note;
    std::unique_ptr <InotePlayer> note_player;

    std::chrono::steady_clock::time_point m_time_begin_to_press;
    
    bool is_right_button_pressed = false;

public:
    Model();
    void update(const RealButtons&);

    void pressRingButton();
    void releaseRingButton();
};
