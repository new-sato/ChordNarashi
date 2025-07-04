#include "ChordButtonManager.hpp"

using namespace std;

ChordButtonManager::ChordButtonManager()
{
    real_chord_buttons = vector<Button>(NUM_OF_CHORD_BUTTON);
    virtual_chord_buttons = set<int>();
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

/// @brief virtual_chord_buttonsをアップデートする
void ChordButtonManager::update_vcb_state()
{
    bool need_to_clear_vcb;

    //virtual_chord_buttonsのクリアが必要かどうかを判定し、
    //no_button_has_been_pressedも更新するための場合分け
    if(is_all_button_releaced())
    {
        // すべてのボタンが押されていないので、何もする必要がない
        no_button_has_been_pressed = true;
        return;
    }
    else 
    {
        //HACK
        if(no_button_has_been_pressed == true)
        {
            // なにも押されていないところから新たにボタンが押されたので、
            // 全消しして更新を行う
            no_button_has_been_pressed = false;
            need_to_clear_vcb = true;
        }
        else
        {
            // ボタンが押されっぱなしの場合
            need_to_clear_vcb = false;
        }
    }

    //HACK
    if(need_to_clear_vcb)
    {
        virtual_chord_buttons.clear();
        for(int i=0; i < NUM_OF_CHORD_BUTTON; i++)
        {
            if(real_chord_buttons[i].getIsPressed())
            {
                virtual_chord_buttons.insert(i);
            }
        }
    }
    else
    {
        for(int i; i < NUM_OF_CHORD_BUTTON; i++)
        {
            // trueならばそのまま更新しない
            if(real_chord_buttons[i].getIsPressed())
            {
                virtual_chord_buttons.insert(i);
            }
        }
    }
}
