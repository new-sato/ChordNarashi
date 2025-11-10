#pragma once

#include "INotePlayer.hpp"

#include <chrono>
#include <memory>

class Model
{
    ChordButtonManager chord_button_manager;
    Button2Chord button_to_chord;
    std::unique_ptr<Ichord2Note> m_chord_to_note;
    std::unique_ptr<InotePlayer> m_note_player;

    std::chrono::steady_clock::time_point m_time_begin_to_press;
    
    bool is_right_button_pressed = false;

public:
    Model(std::unique_ptr<Ichord2Note>, std::unique_ptr<InotePlayer>);
    void updateChord(const RealButtons&);

    void pressRingButton();
    void releaseRingButton();
    
    void addPlayObserver(std::function<void(const NotePlayInformation&)>);
    void addKeyObserver(std::function<void(int)>);
};
