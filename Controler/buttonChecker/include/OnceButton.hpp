#pragma once

class OnceButton
{
    bool m_has_button_pressed = false;
    bool m_button_state = false;
    
public:
    void setState(bool is_button_pressed);
    bool getState()const{return m_button_state;}
};