#include "ChordButtonManager.hpp"
#include <iostream>

using namespace std;

// HACK ラムダ式ではなくヘルパー関数として実装したほうがテストしやすくて無難か
VirtualChordButton::VirtualChordButton(int button_num, int key)
    :note
    (
        static_cast<Note>
        (
            [=]() -> int
            {
                enum FifthLocDiff
                {
                    Major = 0,
                    minor = 3,
                    dim = 5,
                    arg = 0,
                    sus = 0
                };
                ChordButtonType c = static_cast<ChordButtonType>(button_num / static_cast<int>(Note::end));

                // 五度円上のどこにいるか
                int loc = (button_num+key) % NUM_OF_NOTE;
                switch (c)
                {
                case ChordButtonType::Major:
                    return (loc + FifthLocDiff::Major)%12;
                    break;
                case ChordButtonType::minor:
                    return (loc + FifthLocDiff::minor)%12;
                case ChordButtonType::dim:
                    return (loc + FifthLocDiff::dim)%12;
                default:
                    return loc;
                    break;
                }
            }()
        )
    )
    ,cbt(static_cast<ChordButtonType>(button_num / static_cast<int>(Note::end)))
{    
}

VirtualChordButton VirtualChordButton::shift(unsigned int shift_diff)
{
    int note_int = static_cast<int>(note);
    Note shifted_note = static_cast<Note>((note_int + shift_diff)%12);
    return VirtualChordButton(cbt, shifted_note);
}

int VirtualChordButton::ButtonNum()const
{
    return static_cast<int>(cbt)*12 + static_cast<int>(note);
}

std::vector<std::string> note_str_map_hoge
{
    "C",
    "G",
    "D",
    "A",
    "E",
    "B",
    "F♯",
    "D♭",
    "A♭",
    "E♭",
    "B♭",
    "F"
};


ChordButtonManager::ChordButtonManager(KeyButtonChecker& k, vector<Button>& real_button_arg, vector<Button>& shift_button_arg)
    :key_button_checker(k), real_chord_buttons(real_button_arg), shift_buttons(shift_button_arg)
{
    virtual_chord_buttons = set<VirtualChordButton>();
    no_button_has_been_pressed = true;
}

bool ChordButtonManager::is_all_button_releaced()
{
    for(Button b: real_chord_buttons)
    {
        if(b.getIsPressed())
        {
            return false;
        }
    }
    return true;
}

void ChordButtonManager::update_vkb_state()
{
    addKey(key_button_checker.getKeyButtonState());
}

/// @brief RealChordButtonとshiftButtonをチェックし、virtual_chord_buttonsをアップデートする
void ChordButtonManager::update_vcb_state()
{
    //virtual_chord_buttonsのクリアが必要かどうかを判定し、
    //no_button_has_been_pressedも更新するための場合分け
    // TODO is_all_button_releacedの判定に、キーずらしボタンも含める
    if(is_all_button_releaced())
    {
        // すべてのボタンが押されていないので、何もする必要がない
        no_button_has_been_pressed = true;
        return;
    }
    
    if(no_button_has_been_pressed == true)
    {
        // なにも押されていないところから新たにボタンが押されたので、
        // 全消しして更新を行う
        no_button_has_been_pressed = false;
        virtual_chord_buttons.clear();
        temp_shift = 0;
    }

    for(int i=0; i < NUM_OF_CHORD_BUTTON; i++)
    {
        if(real_chord_buttons[i].getIsPressed())
        {
            virtual_chord_buttons.insert(VirtualChordButton(i,key));
        }
    }
    for(int i=0; i < NUM_OF_NOTE; i++)
    {
        if(shift_buttons[i].getIsPressed())
        {
            temp_shift = i;
        }
    }
}

void::ChordButtonManager::updateState()
{
    update_vkb_state();
    update_vcb_state();
}

void ChordButtonManager::setKey(unsigned int new_key)
{
    // ボタンが押されている間は入力を受け付けない
    if(!is_all_button_releaced()) return;

    if(key != new_key)
    {
        key = new_key % 12;
        std::cout << "key = " << note_str_map_hoge[key] << std::endl;
    }
    
}

std::set<VirtualChordButton> ChordButtonManager::getVirtualChordButtons() const
{
    if(temp_shift == 0)
    {
        return virtual_chord_buttons;
    }
    std::set<VirtualChordButton> vcb_to_return;
    for(VirtualChordButton v: virtual_chord_buttons)
    {
        vcb_to_return.insert(v.shift(temp_shift));
    }
    return vcb_to_return;
}
