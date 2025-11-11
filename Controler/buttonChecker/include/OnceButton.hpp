#pragma once

class OnceButton
{
    bool m_has_button_pressed = false;
    
public:
    bool updateAndGetState(bool is_button_pressed);
};