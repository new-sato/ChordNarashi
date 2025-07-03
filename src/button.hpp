class Button
{
    protected:
    bool is_pressed = false;

    public:
    virtual bool getIsPressed() const{return is_pressed;}
    virtual void setIsPressed(bool new_state){is_pressed = new_state;}
};