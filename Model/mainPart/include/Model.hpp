#pragma once

#include "INotePlayer.hpp"
#include "IringButtonTimingManager.hpp"

#include <chrono>
#include <memory>

class Model
{
    std::unique_ptr<IringButtonTimingManager> m_ring_button_timing_mng;
    ChordButtonManager chord_button_manager;
    Button2Chord button_to_chord;
    std::unique_ptr<Ichord2Note> m_chord_to_note;
    std::unique_ptr<InotePlayer> m_note_player;

    std::chrono::steady_clock::time_point m_time_begin_to_press;
    
    /// @brief ボタンが押され始めた時に呼び出される。ここで初めてノートが生成される
    void startRingingNote();
    
    /// @brief ボタンが押され続けているときに呼ばれる
    void sustainRingingNote();


public:
    Model(std::unique_ptr<Ichord2Note>, std::unique_ptr<InotePlayer>, std::unique_ptr<IringButtonTimingManager>);
    void updateChord(const RealButtons&);
    void updateKey(std::vector<bool>);
    void processRingButtonState(bool is_ring_button_pressed, bool is_sustain_button_pressed);

    /// @brief 鳴らされている音を止める。処理の終了時に読んでやる必要があるのでpublic
    void stopRingingNote();
    
    void addPlayObserver(std::function<void(const NotePlayInformation&)>);
    void addKeyObserver(std::function<void(int)>);
    void addRingingChordObserver(std::function<void(const ChordName&)>);
};
