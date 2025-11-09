#pragma once

#include "IMidiNotePlayer.hpp"
#include "UI.hpp"

class View
{
    IMidiNotePlayer& m_midi_note_player;
    UI m_UI;
public:
    View(IMidiNotePlayer& midi_note_player, Idisplay& display);
    void updateView(std::chrono::milliseconds d_time);
    
    /// @brief ウィンドウの状態をといあわせ、メインループを継続すべきかどうかについて伝える
    /// @return ウィンドウを閉じるならtrue
    bool stopLoop();
};