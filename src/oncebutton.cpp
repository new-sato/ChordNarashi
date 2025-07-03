#include "oncebutton.hpp"

bool OnceButton::getIsPressed() const
{
    if(is_pressed && is_first_press)
    {
        is_first_press = false;
        return true;
    }
    else return false;
}

void OnceButton::setIsPressed(bool new_state)
{
    if(new_state==false)
    {
        is_first_press = true;
    }

    is_pressed = new_state;
}
