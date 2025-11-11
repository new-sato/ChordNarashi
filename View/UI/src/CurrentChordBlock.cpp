#include "CurrentChordBlock.hpp"
#include "UI.hpp"

using namespace std;

void CurrentChordBlock::changeRingingChord(const ChordName &) {}

CurrentChordBlock::CurrentChordBlock(const UI &ui, Model &model)
    : Block(1.0, 1.0, 0, 0.5), m_ui(ui)
{
    model.addRingingChordObserver(
        [this](const ChordName& c)
        {
            this->changeRingingChord(c);
        }
    );
}

void CurrentChordBlock::updateBlock(std::chrono::milliseconds)
{
    m_chara_to_display.clear();
    m_chara_to_display.push_back(charaDataInBlock(0, 0, 24, "test"));
}
