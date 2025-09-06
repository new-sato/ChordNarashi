#pragma once
#include "button.hpp"
#include "keyButtonChecker.hpp"
#include "enumNote.hpp"

#include <vector>
#include <set>
#include <string>

enum class ChordButtonType
{
    Major,
    minor,
    dim,
    arg,
    sus4,
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
    
    VirtualChordButton shift(unsigned int shift_diff);

    int ButtonNum() const;
    bool operator<(const VirtualChordButton& right) const {return this->ButtonNum() < right.ButtonNum();}
};

/// @brief 和音のボタンとキーマネージャーを配下に持ち、ボタンの読み取り、ボタン押下の継続や記憶などを行い、どのコードのボタンが押されたのかを特定する。
class ChordButtonManager
{
    std::vector<Button>& shift_buttons;
    std::vector<Button>& real_chord_buttons;
    std::set<VirtualChordButton> virtual_chord_buttons;
    
    KeyButtonChecker& key_button_checker;

    int key = 0;
    int temp_shift = 0;

    bool no_button_has_been_pressed;
    int update_vkb_state();

public:
    ChordButtonManager(KeyButtonChecker& k, std::vector<Button>& real_button_arg, std::vector<Button>& shift_button_arg);
    ChordButtonManager(std::vector<OnceButton>& key_buttons, std::vector<Button>& chord_buttons, std::vector<Button>& shift_buttons)
        :ChordButtonManager(*new KeyButtonChecker(key_buttons), chord_buttons, shift_buttons){}

    // HACK:テストの都合でpublicにしてある。そのうちprivateにする
    void update_vcb_state();
    bool is_all_button_releaced();
    
    int updateState();

    /// @brief キーを直接設定する。11以上なら12で割った剰余の番号のキーに設定される。ただし、キーの変更はコードボタンが押されていないときのみ行われる。
    /// @param new_key 新しいキーを正の整数で指定する。
    /// @return ずらした結果の番号を返す
    int setKey(unsigned int new_key);

    /// @brief 現在のキーを五度円の時計回り方向にずらす。
    /// @param key_diff 正の整数で、どれだけずらすかを指定する。
    /// @return ずらした結果の番号を返す
    int addKey(unsigned int key_diff)
    {
        return setKey(key + key_diff);
    }

    int getKey()const{ return key; }

    std::set<VirtualChordButton> getVirtualChordButtons()const;

    /// @brief n番目のボタンの状態（押されているかいないか）をstateにする
    /// @param n ボタンの番号
    /// @param state 設定したい状態
    void setRealButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};