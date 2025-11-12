#include "UI.hpp"
#include "KeyBlock.hpp"
#include "RingingChordBlock.hpp"
#include "CurrentPressedChordBlock.hpp"
#include "DisplayCircleBlock.hpp"

using namespace std;

KeySignatureMode& operator++(KeySignatureMode& mode)
{
    switch (mode)
    {
    case KeySignatureMode::STANDARD:
        return mode = KeySignatureMode::ALL_FLAT;
        break;
    case KeySignatureMode::ALL_FLAT:
        return mode = KeySignatureMode::ALL_SHARP;
        break;
    case KeySignatureMode::ALL_SHARP:
        return mode = KeySignatureMode::STANDARD;
        break;
    default:
        return mode = KeySignatureMode::STANDARD;
        break;
    }
}

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
    m_blocks.push_back(std::make_unique<RingingChordBlock>(*this,model));
    m_blocks.push_back(std::make_unique<DisplayCircle>(*this, model));
    m_blocks.push_back(std::make_unique<CurrentPressedChordBlock>(*this, model));
}

std::map<ChordType, string> chord_type_table = {
    {Major, ""},
    {minor,"m"},
    {dim, "dim"},
    {arg, "arg"},
    {sus4, "sus4"},
    {sev, "7"},
    {Msev,"M7"},
    {msev,"m7"},
    {mMsev,"mM7"},
    {dimsev,"dim7"},
    {argsev,"arg7"},
    {sevsus4,"7sus4"},
    {Msevsus4, "M7sus4"},
    {add9, "add9"},
};


std::string UI::getChordNameStr(const ChordName &input)const
{
    string ans;
    std::string root_note_str = m_key_str[static_cast<int>(input.root_note)];
    ans.append(root_note_str);
    
    std::string chord_type_str = chord_type_table[input.chord_type];
    ans.append(chord_type_str);
    
    return ans;
}

void UI::toggleSharpFlat()
{
    ++m_key_signature_mode;
    m_key_str = m_key_str_table[m_key_signature_mode];
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
