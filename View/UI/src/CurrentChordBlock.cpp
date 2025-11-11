#include "CurrentChordBlock.hpp"
#include "UI.hpp"

using namespace std;

CurrentChordBlock::CurrentChordBlock(const UI &ui, Model& model):
    Block(1.0, 1.0, 0, 0.5), m_ui(ui)
{
    model.addRingingChordObserver(
        [this](const ChordName& c)
        {
            this->changeRingingChord(c);
        }
    );
}
