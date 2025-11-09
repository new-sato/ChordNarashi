#include "View.hpp"

View::View(IMidiNotePlayer& midi_note_player, Idisplay& display):
    m_midi_note_player(midi_note_player),
    m_UI(UI(display))
{
}

void View::updateView(std::chrono::milliseconds d_time)
{
    m_UI.updateUI(d_time);
}

bool View::stopLoop()
{
    return m_UI.get_x_button_pressed();
}
