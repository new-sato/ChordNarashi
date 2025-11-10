class IringButtonTimingManager
{
    bool is_button_pressed = false;
public:
    virtual bool mustStopNote() = 0;
    virtual bool mustStartNote() = 0;

    void setButtonState(bool state){is_button_pressed = state;}
};