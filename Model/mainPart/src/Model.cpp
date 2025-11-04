#include "Model.hpp"

void Model::update(const RealButtons& input)
{
    chord_button_manager.update_state(input);

    auto virtual_chord_buttons = chord_button_manager.getVirtualChordButtons();
    button_to_chord.updateChord(virtual_chord_buttons);

    if(is_right_button_pressed)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = (now - m_time_begin_to_press);
        note_player->playNote(duration.count());
    }
}

void Model::pressRingButton()
{
    
    const ChordName& chord_name = button_to_chord.getChordName();

    auto notes = chord_to_note->generateNote(chord_name);

    note_player->updateNote(notes);
    note_player->playNote(0.0);

    m_time_begin_to_press = std::chrono::steady_clock::now();
    is_right_button_pressed = true;
}

void Model::releaseRingButton()
{
    note_player->stopNote();
    is_right_button_pressed = false;
}
