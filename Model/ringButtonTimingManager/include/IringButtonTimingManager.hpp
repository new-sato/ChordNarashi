#pragma once

class IringButtonTimingManager
{
protected:
    bool is_sustain_button_pressed = false;
    bool is_sustain_button_NOW_pressed = false;
    bool is_sustain_button_NOW_released = false;

    bool is_button_pressed = false;
    bool is_button_NOW_released = false;
    bool is_button_NOW_pressed = false;
public:
    virtual bool mustStopNote() = 0;
    virtual bool mustStartNote() = 0;
    virtual bool mustSustainNote() = 0;

    void setButtonState(bool ring_button_state, bool sustain_button);
};