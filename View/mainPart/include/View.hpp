#pragma once

#include "IMidiNotePlayer.hpp"
#include "Idisplay.hpp"

class View
{
    IMidiNotePlayer& m_midi_note_player;
    Idisplay& m_display;
public:
    View(IMidiNotePlayer& midi_note_player, Idisplay&);
    void updateView(std::chrono::duration<double>);
    
    /// @brief ウィンドウの状態をといあわせ、メインループを継続すべきかどうかについて伝える
    /// @return ウィンドウを閉じるならtrue
    bool stopLoop();
};