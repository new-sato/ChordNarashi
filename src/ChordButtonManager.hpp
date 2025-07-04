#include "button.hpp"
#include <vector>
#include <set>

// 本来は60
const int NUM_OF_CHORD_BUTTON = 60;

const int NUM_OF_NOTE = 12;

/// @brief 和音のボタンを配下に持ち、ボタンの読み取り、ボタン押下の継続や記憶などを担当する。
class ChordButtonManager
{
    std::vector<Button> real_chord_buttons;
    std::set<int> virtual_chord_buttons;
    
    bool no_button_has_been_pressed;
    
    public:
    ChordButtonManager();
    void update_vcb_state();
    bool is_all_button_releaced();

    std::set<int> getVirtualChordButtons()const{return virtual_chord_buttons;}

    /// @brief n番目のボタンの状態（押されているかいないか）をstateにする
    /// @param n ボタンの番号
    /// @param state 設定したい状態
    void setButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};