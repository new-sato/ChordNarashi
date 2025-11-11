#include "OnceButton.hpp"

void OnceButton::setState(bool is_button_pressed)
{
    if(is_button_pressed)
    {
        if(!m_has_button_pressed)
        {
            m_has_button_pressed = true;
            m_button_state = true;
        }
        else
        {
            m_button_state = false;
        }
    }
    else
    {
        m_has_button_pressed = false;
        m_button_state = false;
    }
}
