#include "View.hpp"

View::View(IMidiNotePlayer& midi_note_player, Idisplay& display):
    m_midi_note_player(midi_note_player),
    m_display(display)
{
}

void View::updateView(std::chrono::duration<double>)
{
    m_display.updateDisplay();
}

bool View::stopLoop()
{
    return m_display.is_x_button_pressed();
}
