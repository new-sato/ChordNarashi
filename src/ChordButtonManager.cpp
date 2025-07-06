#include "ChordButtonManager.hpp"

using namespace std;

// HACK ラムダ式ではなくヘルパー関数として実装したほうがテストしやすくて無難か
VirtualChordButton::VirtualChordButton(int button_num)
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
                int loc = button_num % NUM_OF_NOTE;
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

int VirtualChordButton::ButtonNum()const
{
    return static_cast<int>(cbt)*12 + static_cast<int>(note);
}

ChordButtonManager::ChordButtonManager()
{
    real_chord_buttons = vector<Button>(NUM_OF_CHORD_BUTTON);
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

/// @brief virtual_chord_buttonsをアップデートする
void ChordButtonManager::update_vcb_state()
{
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
            virtual_chord_buttons.clear();
        }
    }

    for(int i=0; i < NUM_OF_CHORD_BUTTON; i++)
    {
        if(real_chord_buttons[i].getIsPressed())
        {
            virtual_chord_buttons.insert(VirtualChordButton(i));
        }
    }
}
