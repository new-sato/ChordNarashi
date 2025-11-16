#include "RingingChordBlock.hpp"
#include "UI.hpp"
#include "map"


using namespace std;

void RingingChordBlock::setRingingChordName(const ChordName &input)
{
    m_ringing_chord_name = m_ui.getChordNameStr(input);
}

void RingingChordBlock::changeRingingChord(const ChordName &input)
{
    setRingingChordName(input);
}

RingingChordBlock::RingingChordBlock(const UI &ui, Model &model)
    : Block(1.0, 1.0, 0, 0.2), m_ui(ui)
{
    model.addRingingChordObserver(
        [this](const ChordName& c)
        {
            this->changeRingingChord(c);
        }
    );
}

void RingingChordBlock::updateBlock(std::chrono::milliseconds)
{
    m_chara_to_display.clear();
    m_chara_to_display.push_back(charaDataInBlock(0, 0, 24, m_ringing_chord_name));
}
