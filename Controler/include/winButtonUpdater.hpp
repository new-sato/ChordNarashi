#pragma once
#include "ButtonUpdater.hpp"
#include "other_button.hpp"
#include <windows.h>
#include <vector>

class winButtonUpdater:public ButtonUpdater
{
    
    void checkButton(Button& button,int key);
    void checkButton(Button& button,std::vector<int> keys);
    
    bool easyModeFlag = 1;

    public:
    winButtonUpdater(
        std::vector<Button>& chordButtonsArg,
        std::vector<Button>& shiftButtonsArg,
        std::vector<OnceButton>& keyButtonsArg,
        std::vector<Button>& rightButtonsArg,
        std::vector<OnceButton>& otherButtonArg,
        Button& sustainButtonArg
    )
    :ButtonUpdater(chordButtonsArg,shiftButtonsArg,keyButtonsArg,rightButtonsArg,otherButtonArg,sustainButtonArg){}
    void updateAllButtons() override;
    void toggleEasyModeFlag(){easyModeFlag = !easyModeFlag;}
};
