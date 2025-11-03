#include "Model.hpp"

void Model::update(const RealButtons& input)
{
    chord_button_manager.update_state(input);
    if(is_right_button_pressed)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = (now - m_time_begin_to_press);
        // TODO std::chronoの型変換をなんとかする
        standard_note_player.playNote(0.0);
    }
}

void Model::pressRingButton()
{
    auto virtual_chord_buttons = chord_button_manager.getVirtualChordButtons();
    
    button_to_chord.updateChord(virtual_chord_buttons);
    
    auto chord_name = button_to_chord.getChordName();

    auto notes = chord_to_standard_note.generateNote(chord_name);

    standard_note_player.updateNote(notes);
    standard_note_player.playNote(0.0);

    m_time_begin_to_press = std::chrono::steady_clock::now();
    is_right_button_pressed = true;
}

void Model::releaseRingButton()
{
    standard_note_player.stopNote();
    is_right_button_pressed = false;
}
