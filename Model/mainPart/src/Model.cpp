#include "Model.hpp"

Model::Model
(   std::unique_ptr<Ichord2Note>chord2note,
    std::unique_ptr<InotePlayer>note_player,
    std::unique_ptr<IringButtonTimingManager> rbtm
):
    m_chord_to_note(std::move(chord2note)),
    m_note_player(std::move(note_player)),
    m_ring_button_timing_mng(std::move(rbtm))
{
}

void Model::updateChord(const RealButtons &input)
{
    chord_button_manager.update_state(input);

    auto virtual_chord_buttons = chord_button_manager.getVirtualChordButtons();
    button_to_chord.updateChord(virtual_chord_buttons);

}

void Model::updateKey(std::vector<bool> input)
{
    for(int i = 0; i< input.size();i++)
    {
        if(input[i]==true)
            chord_button_manager.addKey(i);
    }
}

void Model::processRingButtonState(bool is_ring_button_pressed, bool is_sustain_button_pressed)
{
    m_ring_button_timing_mng->setButtonState(is_ring_button_pressed, is_sustain_button_pressed);

    if(m_ring_button_timing_mng->mustStopNote())
    {
        stopRingingNote();
    }
    if(m_ring_button_timing_mng->mustStartNote())
    {
        startRingingNote();
    }
    else if(m_ring_button_timing_mng->mustSustainNote())
    {
        sustainRingingNote();
    }
}

void Model::startRingingNote()
{
    
    const ChordName& chord_name = button_to_chord.getChordName();

    auto notes = m_chord_to_note->processNote(chord_name);

    m_note_player->updateNote(notes);
    // 鳴らし始めなので0.0を指定
    m_note_player->playNote(0.0);

    m_time_begin_to_press = std::chrono::steady_clock::now();
}

void Model::sustainRingingNote()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = (now - m_time_begin_to_press);
    m_note_player->playNote(duration.count());
}

void Model::stopRingingNote()
{
    m_note_player->stopNote();
}

void Model::addPlayObserver(std::function<void(const NotePlayInformation &)> arg)
{
    m_note_player->addPlayObserver(arg);
}

void Model::addKeyObserver(std::function<void(int)>func)
{
    chord_button_manager.addKeyObserver(func);
}

void Model::addRingingChordObserver(std::function<void(const ChordName &)>func)
{
    m_chord_to_note->addRingingChordObserver(func);
}

void Model::addCurrentChordObserver(std::function<void(const ChordName &)>func)
{
    button_to_chord.addCurrentChordObserver(func);
}

void Model::addPressedButtonObserver(std::function<void(const std::vector<VirtualChordButton> &)>func)
{
    button_to_chord.addPressedButtonObserver(func);
}
