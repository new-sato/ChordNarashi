#include "UI.hpp"

using namespace std;

void UI::registCharacter()
{
    for(auto c:m_chara_data_to_display)
    {
        m_display.displayCharacter(c);
    }
}

UI::UI(Idisplay &display) : m_display(display)
{
    //TODO テスト用
    m_blocks.push_back(Block(2.0, 1.0, 0, 0));
}

void UI::updateUI(chrono::milliseconds d_time)
{
    for(auto b:m_blocks)
    {
        b.updateBlock(d_time);
        vector<charaData> chara_to_disp = b.getCharaToDisplay();
        for(auto c: chara_to_disp)
        {
            m_chara_data_to_display.push_back(c);
        }
    }
    registCharacter();
    
    m_display.updateDisplay();
}
