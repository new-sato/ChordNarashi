class Button
{
    bool is_pressed = false;

    public:
    bool getIsPressed() const{return is_pressed;}
    void setIsPressed(bool state){is_pressed = state;}
};