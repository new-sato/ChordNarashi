#include "onceButton.hpp"
#include <vector>

class ButtonUpdater
{
    protected:
    //HACK 参照の配列にすべきだった
    std::vector<Button> &chordButtons;
    std::vector<Button> &shiftButtons;
    std::vector<OnceButton> &keyButtons;
    std::vector<Button> &rightButtons;
    std::vector<OnceButton> &otherButtons;
    Button &sustainButton;

    public:
    ButtonUpdater(
        std::vector<Button>& chordButtonsArg,
        std::vector<Button>& shiftButtonsArg,
        std::vector<OnceButton>& keyButtonsArg,
        std::vector<Button>& rightButtonsArg,
        std::vector<OnceButton>& otherButtonsArg,
        Button& sustainButtonArg
    )
    :chordButtons(chordButtonsArg)
    ,shiftButtons(shiftButtonsArg)
    ,keyButtons(keyButtonsArg)
    ,rightButtons(rightButtonsArg)
    ,otherButtons(otherButtonsArg)
    ,sustainButton(sustainButtonArg){}

    virtual void updateAllButtons() = 0;
};
