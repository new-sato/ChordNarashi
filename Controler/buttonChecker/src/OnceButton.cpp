#include "OnceButton.hpp"

bool OnceButton::updateAndGetState(bool is_button_pressed)
{
    if(is_button_pressed)
    {
        if(!m_has_button_pressed)
        {
            m_has_button_pressed = true;
            return true;
        }
    }
    else
    {
        m_has_button_pressed = false;
    }
    return false;
}
