#include "ChordButtonManager.hpp"
#include <iostream>

using namespace std;


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


/// @brief RealChordButtonとshiftButtonをチェックし、キーの状態とコードの状態をアップデートする
void ChordButtonManager::update_state(const RealButtons& input)
{
    //virtual_chord_buttonsのクリアが必要かどうかを判定し、
    //no_button_has_been_pressedも更新するための場合分け
    if(input.IsAllChordButtonReleased())
    {
        // すべてのボタンが押されていないので、キーのボタンが押されていないかを見る
        for(int i=0;i<NUM_OF_NOTE;i++)
        {
            if(input.keyButtons[i] == true)
            {
                addKey(i);
            }
        }

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

    for(pair<ChordButtonType, vector<bool>> p: input.chordButtons)
    {
        for(int i=0; i<p.second.size();i++)
        {
            if(p.second[i])
            {
                virtual_chord_buttons.insert(VirtualChordButton(p.first, i, key));
            }
        }
    }
    for(int i=0; i < NUM_OF_NOTE; i++)
    {
        if(input.tempShihftButtons[i])
        {
            temp_shift = i;
        }
    }
}


int ChordButtonManager::setKey(unsigned int new_key)
{
    if(!no_button_has_been_pressed) return key;
    notify_key_change(new_key);
    if(key != new_key)
    {
        key = new_key % 12;
        return key;
    }
    return key;
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

bool RealButtons::IsAllChordButtonReleased()const
{
    for(std::pair<ChordButtonType, std::vector<bool>> p: chordButtons)
    {
        for(bool state : p.second)
        {
            if(state == true) return false;
        }
    }
    return true;
}
