#include "ButtonUpdater.hpp"
#include "other_button.hpp"
#include <windows.h>

class winButtonUpdater:public ButtonUpdater
{
    
    void checkButton(Button& button,int key);

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
};
