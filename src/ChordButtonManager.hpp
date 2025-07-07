#pragma once
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
    /// @brief 押されたボタンの番号と現在のキーを基に、どのコードに対応するかを決定
    /// @param button_num 押されているRealButtonの番号
    /// @param key 現在のキー
    VirtualChordButton(int button_num, int key);

    int ButtonNum() const;
    bool operator<(const VirtualChordButton& right) const {return this->ButtonNum() < right.ButtonNum();}
};

/// @brief 和音のボタンとキーマネージャーを配下に持ち、ボタンの読み取り、ボタン押下の継続や記憶などを行い、どのコードのボタンが押されたのかを特定する。
class ChordButtonManager
{
    std::vector<Button> real_chord_buttons;
    std::set<VirtualChordButton> virtual_chord_buttons;
    
    int key = 0;

    bool no_button_has_been_pressed;

public:
    ChordButtonManager();
    void update_vcb_state();
    bool is_all_button_releaced();

    /// @brief キーを直接設定する。11以上なら12で割った剰余の番号のキーに設定される。ただし、キーの変更はコードボタンが押されていないときのみ行われる。
    /// @param new_key 新しいキーを正の整数で指定する。
    void setKey(unsigned int new_key);

    /// @brief 現在のキーを五度円の時計回り方向にずらす。
    /// @param key_diff 正の整数で、どれだけずらすかを指定する。
    void addKey(unsigned int key_diff){ setKey(key + key_diff); }

    std::set<VirtualChordButton> getVirtualChordButtons()const{return virtual_chord_buttons;}

    /// @brief n番目のボタンの状態（押されているかいないか）をstateにする
    /// @param n ボタンの番号
    /// @param state 設定したい状態
    void setRealButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};