#include "Model.hpp"

Model::Model(std::unique_ptr<Ichord2Note> chord2note, std::unique_ptr<InotePlayer>note_player)
:m_chord_to_note(std::move(chord2note)), m_note_player(std::move(note_player)) 
{}

void Model::updateChord(const RealButtons &input)
{
    chord_button_manager.update_state(input);

    auto virtual_chord_buttons = chord_button_manager.getVirtualChordButtons();
    button_to_chord.updateChord(virtual_chord_buttons);

    if(is_right_button_pressed)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = (now - m_time_begin_to_press);
        m_note_player->playNote(duration.count());
    }
}

void Model::pressRingButton()
{
    
    const ChordName& chord_name = button_to_chord.getChordName();

    auto notes = m_chord_to_note->generateNote(chord_name);

    m_note_player->updateNote(notes);
    // 鳴らし始めなので0.0を指定
    m_note_player->playNote(0.0);

    m_time_begin_to_press = std::chrono::steady_clock::now();
    is_right_button_pressed = true;
}

void Model::releaseRingButton()
{
    m_note_player->stopNote();
    is_right_button_pressed = false;
}

void Model::addPlayObserver(std::function<void(const NotePlayInformation &)> arg)
{
    m_note_player->addPlayObserver(arg);
}

void Model::addKeyObserver(std::function<void(int)>func)
{
    chord_button_manager.addKeyObserver(func);
}
