#include "Button2Chord.hpp"
#include <vector>

using namespace std;

/// @brief コードボタンがひとつしか押されていない時の関数。
/// @param set_of_chord 
void Button2Chord::singleChord(set<VirtualChordButton> set_of_chord)
{
    VirtualChordButton v = *set_of_chord.begin();
    switch(v.cbt)
    {
        case ChordButtonType::Major:
            chord_name.chord_type = ChordType::Major;
            break;
        case ChordButtonType::minor:
            chord_name.chord_type = ChordType::minor;
            break;
        case ChordButtonType::dim:
            chord_name.chord_type = ChordType::dim;
            break;
        case ChordButtonType::arg:
            chord_name.chord_type = ChordType::arg;
            break;
        case ChordButtonType::sus4:
            chord_name.chord_type = ChordType::sus4;
            break;
        default:
            break;
    }
    chord_name.root_note = v.note;
}

void Button2Chord::doubleChord(set<VirtualChordButton> set_of_chord)
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

        chord_name.root_note = vcb1.note;
        chord_name.chord_type = sev;
        return;
    }

    if(vcb2.cbt == ChordButtonType::minor)
    {
        // 1個目がメジャーでないなら違う
        if(vcb1.cbt != ChordButtonType::Major) return;
        
        // ずれがないならマイナーセブンス
        if((static_cast<int>(vcb1.note)+MIN_DIFF)%NUM_OF_NOTE == static_cast<int>(vcb2.note))
        {
            chord_name.root_note = vcb2.note;
            chord_name.chord_type = msev;
            return;
        }
        // 1つズレならメジャーセブンス
        else if((static_cast<int>(vcb1.note)+MIN_DIFF+1)%NUM_OF_NOTE == static_cast<int>(vcb2.note))
        {
            chord_name.root_note = vcb1.note;
            chord_name.chord_type = Msev;
            return;
        }
    }

    if(vcb2.cbt == ChordButtonType::arg)
    {
        // マイナーメジャーセブンスかもしれない
        if(vcb1.cbt == ChordButtonType::minor)
        {
            // ずれなしでないなら違う
            if(static_cast<int>(vcb1.note) != (static_cast<int>(vcb2.note)+MIN_DIFF)%12) return;
            chord_name.root_note = vcb1.note;
            chord_name.chord_type = mMsev;
            return;
        }
    }
}

/// @brief 押されているコードボタンからコードネームを決定し、配下の関数を使ってchord_nameに格納する。
void Button2Chord::updateChord()
{
    set<VirtualChordButton> pressed_chord = cbm.getVirtualChordButtons();
    // TODO 場合分けを完成させる
    int num_of_pressed_button = pressed_chord.size();
    switch (num_of_pressed_button)
    {
    case 0:
        break;
    
    case 1:
        singleChord(pressed_chord);
        break;
    case 2:
        doubleChord(pressed_chord);
    case 3:
    default:
        break;
    }
}