#include "IringButtonTimingManager.hpp"

void IringButtonTimingManager::setButtonState(bool is_pressed)
{
    //HACK 細かいこと考えるのがめんどくさいのでこうしておく
    is_button_NOW_pressed = false;
    is_button_NOW_released = false;
    

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