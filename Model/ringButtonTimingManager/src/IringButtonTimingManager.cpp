#include "IringButtonTimingManager.hpp"

void IringButtonTimingManager::setButtonState(bool is_pressed, bool newest_is_sustain_button_pressed)
{
    //HACK 細かいこと考えるのがめんどくさいのでこうしておく
    is_button_NOW_pressed = false;
    is_button_NOW_released = false;
    is_sustain_button_NOW_pressed = false;
    is_sustain_button_NOW_released = false;
    
    // 押されているという最新の情報で押されているなら
    if(newest_is_sustain_button_pressed==true)
    {
        // さっきまで押されてなかったなら
        if(is_sustain_button_pressed == false)
        {
            is_sustain_button_NOW_pressed = true;
            is_sustain_button_pressed = true;
        }
    }
    else
    {
        // 以下押されてない場合
        // さっきまで押されてたなら
        if(is_sustain_button_pressed == true)
        {
            is_sustain_button_NOW_released = true;
            is_sustain_button_pressed = false;
        }
    }

    if(is_pressed)
    {
        if(is_button_pressed == false)
        {
            is_button_NOW_pressed = true;
            is_button_pressed = true;
        }
    }
    else
    {
        if(is_button_pressed == true)
        {
            is_button_NOW_released = true;
            is_button_pressed = false;
        }
    }
}