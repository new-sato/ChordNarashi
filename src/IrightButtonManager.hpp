#pragma once
#include <vector>
#include "button.hpp"

struct rightButtonState
{
    bool is_pressed;
    std::vector<bool> state;
};

enum class rightButtonInfo
{
    mainButton,
    NUM_OF_BUTTON
};

class IrightButtonManager
{
    protected:

    const std::vector<Button> &rightButtons;
    public:
    IrightButtonManager(std::vector<Button>& rightbuttonsarg):rightButtons(rightbuttonsarg){}
    virtual rightButtonState getRightButtonState(){return rightButtonState{true,{}};}
};