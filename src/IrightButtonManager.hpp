#pragma once
#include <vector>
#include "button.hpp"

struct rightButtonState
{
    bool is_pressed;
    std::vector<bool> state;
};

class IrightButtonManager
{
    const std::vector<Button>& rightButtons;
    public:
    IrightButtonManager(std::vector<Button>& rightbuttonsarg):rightButtons(rightbuttonsarg){}
    virtual rightButtonState getRightButtonState(){return rightButtonState{true,{}};}
};