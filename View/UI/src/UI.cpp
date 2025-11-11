#include "UI.hpp"
#include "KeyBlock.hpp"
#include "CurrentChordBlock.hpp"

using namespace std;

void UI::registCharacter()
{
    for(auto c:m_chara_data_to_display)
    {
        m_display.displayCharacter(c);
    }
}

UI::UI(Idisplay &display, Model& model) : m_display(display)
{
    m_blocks.push_back(std::make_unique<KeyBlock>(*this,model));
    m_blocks.push_back(std::make_unique<CurrentChordBlock>(*this,model));
}

void UI::updateUI(chrono::milliseconds d_time)
{
    m_chara_data_to_display.clear();
    for(auto& b:m_blocks)
    {
        b->updateBlock(d_time);
        vector<charaData> chara_to_disp = b->getCharaToDisplay();
        for(auto c: chara_to_disp)
        {
            m_chara_data_to_display.push_back(c);
        }
    }
    registCharacter();
    
    m_display.updateDisplay();
}
