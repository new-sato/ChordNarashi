#include "rightButtonBasic.hpp"

rightButtonState RightButtonBasic::getRightButtonState()
{
    rightButtonState ans;
    ans.is_pressed = rightButtons[static_cast<int>(rightButtonInfo::mainButton)].getIsPressed();
    return rightButtonState();
}
