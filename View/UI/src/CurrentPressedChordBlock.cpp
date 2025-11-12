#include "CurrentPressedChordBlock.hpp"
#include "UI.hpp"

void CurrentPressedChordBlock::updateCurrentChord(const ChordName &input)
{
    m_current_chord = input;
}

CurrentPressedChordBlock::CurrentPressedChordBlock(const UI &ui, Model &model):
    Block(1.0, 1.0, 0, 0.1), m_ui(ui)
{
    model.addCurrentChordObserver(
        [this](const ChordName& c)
        {
            this->updateCurrentChord(c);
        }
    );
}

void CurrentPressedChordBlock::updateBlock(std::chrono::milliseconds)
{
    m_chara_to_display.clear();
    m_chara_to_display.push_back(charaDataInBlock(0,0,24,m_ui.getChordNameStr(m_current_chord)));
}
