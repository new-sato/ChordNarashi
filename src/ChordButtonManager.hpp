#include "button.hpp"
#include <vector>
#include <set>

// 本来は60
const int NUM_OF_CHORD_BUTTON = 60;

const int NUM_OF_NOTE = 12;

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
    F
};

struct VirtualChordButton
{
    const ChordButtonType cbt;
    const Note n;

    VirtualChordButton(ChordButtonType type,Note note):cbt(type),n(note){}
    VirtualChordButton(int button_num);
};

/// @brief 和音のボタンを配下に持ち、ボタンの読み取り、ボタン押下の継続や記憶などを担当する。
class ChordButtonManager
{
    std::vector<Button> real_chord_buttons;
    std::set<VirtualChordButton> virtual_chord_buttons;
    
    bool no_button_has_been_pressed;

public:
    ChordButtonManager();
    void update_vcb_state();
    bool is_all_button_releaced();

    std::set<VirtualChordButton> getVirtualChordButtons()const{return virtual_chord_buttons;}

    /// @brief n番目のボタンの状態（押されているかいないか）をstateにする
    /// @param n ボタンの番号
    /// @param state 設定したい状態
    void setButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};