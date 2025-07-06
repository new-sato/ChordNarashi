#include "button.hpp"
#include <vector>
#include <set>


enum class ChordButtonType
{
    Major,
    minor,
    dim,
    arg,
    sus4,
    end
};

enum class Note
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
const int NUM_OF_CHORD_BUTTON = static_cast<int>(ChordButtonType::end) * static_cast<int>(Note::end);

const int NUM_OF_NOTE = static_cast<int>(Note::end);

struct VirtualChordButton
{
    const ChordButtonType cbt;
    const Note note;

    VirtualChordButton(ChordButtonType type,Note n):cbt(type),note(n){}
    VirtualChordButton(int button_num);

    int ButtonNum() const;
    bool operator<(const VirtualChordButton& right) const {return this->ButtonNum() < right.ButtonNum();}
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
    void setRealButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};