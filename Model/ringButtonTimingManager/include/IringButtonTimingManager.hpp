class IringButtonTimingManager
{
protected:
    bool is_button_pressed = false;
    bool is_button_NOW_released = false;
    bool is_button_NOW_pressed = false;
public:
    virtual bool mustStopNote() = 0;
    virtual bool mustStartNote() = 0;

    void setButtonState(bool state);
    bool get_is_button_pressed(){return is_button_pressed;}
};