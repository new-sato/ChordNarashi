#include "Button2Chord.hpp"
#include <vector>

using namespace std;


void Button2Chord::singleChord(vector<VirtualChordButton> set_of_chord)
{
    VirtualChordButton v = set_of_chord[0];
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

void Button2Chord::updateChord()
{
    vector<VirtualChordButton> pressed_chord = cbm.getVirtualChordButtons();
    // TODO pressed_chordのサイズで場合分けを行う
    int num_of_pressed_button = pressed_chord.size();
    switch (num_of_pressed_button)
    {
    case 0:
        break;
    
    case 1:
        //TODO 普通にコードを鳴らす
        singleChord(pressed_chord);
        break;
    case 2:
        //TODO ２コードの時の処理
    case 3:
        //TODO 3コードの時の処理
    default:
        break;
    }
}