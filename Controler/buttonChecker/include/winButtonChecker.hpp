#pragma once

#include "IButtonChecker.hpp"
#include <windows.h>

class winButtonChecker:public IButtonChecker
{
    bool checkButton(int key);
    
    void updateChordButtons()override;
    void updateShiftButtons()override;
    void updateKeyButtons()override;
    
    void updateModeButtons()override{}
public:
    bool isRingButtonPressed()override;
};
