#include "button.hpp"
#include <vector>


enum ChordButtonType
{
    Major,
    minor,
    dim,
    arg,
    sus4,
    end
};

enum Note
{
    C,
    G,
    D,
    A,
    E,
    B,
    Fs,
    Df,
    Af,
    Ef,
    Bf,
    F,
    end
};

// 本来は60
const int NUM_OF_CHORD_BUTTON = ChordButtonType::end * Note::end;

const int NUM_OF_NOTE = Note::end;

struct VirtualChordButton
{
    const ChordButtonType cbt;
    const Note note;

    VirtualChordButton(ChordButtonType type,Note n):cbt(type),note(n){}
    VirtualChordButton(int button_num);
};

/// @brief 和音のボタンを配下に持ち、ボタンの読み取り、ボタン押下の継続や記憶などを担当する。
class ChordButtonManager
{
    std::vector<Button> real_chord_buttons;
    std::vector<VirtualChordButton> virtual_chord_buttons;
    
    bool no_button_has_been_pressed;

public:
    ChordButtonManager();
    void update_vcb_state();
    bool is_all_button_releaced();

    std::vector<VirtualChordButton> getVirtualChordButtons()const{return virtual_chord_buttons;}

    /// @brief n番目のボタンの状態（押されているかいないか）をstateにする
    /// @param n ボタンの番号
    /// @param state 設定したい状態
    void setButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};