#pragma once

#include "INotePlayer.hpp"

#include <chrono>
#include <memory>

class Model
{
    // TODO 実態ではなくポインタや参照を持つべき
    ChordButtonManager chord_button_manager;
    Button2Chord button_to_chord;
    std::unique_ptr<Ichord2Note> m_chord_to_note;
    std::unique_ptr<InotePlayer> m_note_player;

    std::chrono::steady_clock::time_point m_time_begin_to_press;
    
public:
    Model(std::unique_ptr<Ichord2Note>, std::unique_ptr<InotePlayer>);
    void updateChord(const RealButtons&);

    /// @brief ボタンが押され始めた時に呼び出される。ここで初めてノートが生成される
    void startRingingNote();
    
    /// @brief ボタンが押され続けているときに呼ばれる
    void continueRingingNote();

    /// @brief ボタンが離されたときに呼ばれる
    void stopRingingNote();
    
    void addPlayObserver(std::function<void(const NotePlayInformation&)>);
};
