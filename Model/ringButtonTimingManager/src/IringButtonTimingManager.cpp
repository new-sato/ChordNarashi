#include "IringButtonTimingManager.hpp"

void IringButtonTimingManager::setButtonState(bool is_pressed, bool is_sustain_button_pressed_arg)
{
    //HACK 細かいこと考えるのがめんどくさいのでこうしておく
    is_button_NOW_pressed = false;
    is_button_NOW_released = false;
    is_sustain_button_NOW_pressed = false;
    is_sustain_button_NOW_released = false;
    
    if(is_sustain_button_pressed_arg==true)
    {
        if(is_sustain_button_pressed == false)
        {
            is_sustain_button_NOW_pressed = true;
            is_sustain_button_pressed = true;
        }
    }
    else
    {
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