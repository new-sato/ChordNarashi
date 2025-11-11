#include "CurrentChordBlock.hpp"
#include "UI.hpp"
#include "map"


using namespace std;

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

void CurrentChordBlock::setRingingChordName(const ChordName &input)
{
    string ans;
    std::string root_note_str = m_ui.get_key_str()[static_cast<int>(input.root_note)];
    ans.append(root_note_str);
    
    std::string chord_type_str = chord_type_table[input.chord_type];
    ans.append(chord_type_str);
    
    m_ringing_chord_name = ans;
}

void CurrentChordBlock::changeRingingChord(const ChordName &input)
{
    setRingingChordName(input);
}

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
    m_chara_to_display.push_back(charaDataInBlock(0, 0, 24, m_ringing_chord_name));
}
