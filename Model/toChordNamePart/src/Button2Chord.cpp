#include "Button2Chord.hpp"
#include <vector>

using namespace std;

/// @brief コードボタンがひとつしか押されていない時の関数。
/// @param set_of_chord 
void Button2Chord::singleChord(const set<VirtualChordButton>& set_of_chord)
{
    VirtualChordButton v = *set_of_chord.begin();
    switch(v.cbt)
    {
        case ChordButtonType::Major:
            m_chord_name.chord_type = ChordType::Major;
            break;
        case ChordButtonType::minor:
            m_chord_name.chord_type = ChordType::minor;
            break;
        case ChordButtonType::dim:
            m_chord_name.chord_type = ChordType::dim;
            break;
        case ChordButtonType::arg:
            m_chord_name.chord_type = ChordType::arg;
            break;
        case ChordButtonType::sus4:
            m_chord_name.chord_type = ChordType::sus4;
            break;
        default:
            break;
    }
    m_chord_name.root_note = v.note;
}

void Button2Chord::doubleChord(const set<VirtualChordButton>& set_of_chord)
{
    VirtualChordButton vcb1 = *set_of_chord.begin();
    VirtualChordButton vcb2 = *(++(set_of_chord.begin()));

    // セブンスかもしれないとき
    if(vcb2.cbt == ChordButtonType::dim)
    {
        // 1個目がメジャーでないなら違う
        if(vcb1.cbt != ChordButtonType::Major) return;

        // 11個ずれでないなら違う
        if ((static_cast<int>(vcb1.note)+DIM_DIFF+11)%NUM_OF_NOTE!= static_cast<int>(vcb2.note)) return;

        m_chord_name.root_note = vcb1.note;
        m_chord_name.chord_type = sev;
        return;
    }

    // マイナーセブンス・メジャーセブンスかもしれないとき
    if(vcb2.cbt == ChordButtonType::minor)
    {
        // 1個目がメジャーでないなら違う
        if(vcb1.cbt != ChordButtonType::Major) return;
        
        // ずれがないならマイナーセブンス
        if((static_cast<int>(vcb1.note)+MIN_DIFF)%NUM_OF_NOTE == static_cast<int>(vcb2.note))
        {
            m_chord_name.root_note = vcb2.note;
            m_chord_name.chord_type = msev;
            return;
        }
        // 1つズレならメジャーセブンス
        else if((static_cast<int>(vcb1.note)+MIN_DIFF+1)%NUM_OF_NOTE == static_cast<int>(vcb2.note))
        {
            m_chord_name.root_note = vcb1.note;
            m_chord_name.chord_type = Msev;
            return;
        }
    }

    // sevsus4, Msevsus4かもしれないとき
    if(vcb2.cbt == ChordButtonType::sus4)
    {
        if(vcb1.cbt == ChordButtonType::dim)
        {
            if ((static_cast<int>(vcb2.note)+DIM_DIFF+11)%NUM_OF_NOTE!= static_cast<int>(vcb1.note)) return;
            m_chord_name.root_note = vcb2.note;
            m_chord_name.chord_type = sevsus4;
        }
        else if(vcb1.cbt == ChordButtonType::minor)
        {
            if((static_cast<int>(vcb2.note)+MIN_DIFF+1)%NUM_OF_NOTE != static_cast<int>(vcb1.note))
            m_chord_name.root_note = vcb2.note;
            m_chord_name.chord_type = Msevsus4;
        }
    }

    if(vcb2.cbt == ChordButtonType::arg)
    {
        // マイナーメジャーセブンスかもしれない
        if(vcb1.cbt == ChordButtonType::minor)
        {
            // ずれなしでないなら違う
            if(static_cast<int>(vcb1.note) != (static_cast<int>(vcb2.note)+MIN_DIFF)%12) return;
            m_chord_name.root_note = vcb1.note;
            m_chord_name.chord_type = mMsev;
            return;
        }
    }
    
    //add9かもしれない
    if(vcb2.cbt == ChordButtonType::Major)
    {
        if(vcb2.note==Note::F)
        {
            if(vcb1.note!=Note::C)return;
            m_chord_name.root_note = Note::F;
            m_chord_name.chord_type = add9;
            return;
        }
        //1音ずれでないなら違う
        if((static_cast<int>(vcb1.note)+1)%12 != (static_cast<int>(vcb2.note))%12) return;
        m_chord_name.root_note = vcb1.note;
        m_chord_name.chord_type = add9;
        
    }
}

void Button2Chord::notifyCurrentChord(const ChordName &input)
{
    for(auto func: m_current_chord_observer)
    {
        func(input);
    }
}

/// @brief 押されているコードボタンからコードネームを決定し、配下の関数を使ってchord_nameに格納する。
void Button2Chord::updateChord(const set<VirtualChordButton>& pressed_button)
{
    // TODO 場合分けを完成させる
    int num_of_pressed_button = pressed_button.size();
    switch (num_of_pressed_button)
    {
    case 0:
        break;
    
    case 1:
        singleChord(pressed_button);
        break;
    case 2:
        doubleChord(pressed_button);
    case 3:
    default:
        break;
    }
    
    notifyCurrentChord(m_chord_name);
}

void Button2Chord::addCurrentChordObserver(std::function<void(ChordName)>func)
{
    m_current_chord_observer.push_back(func);
}
