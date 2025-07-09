#include "IrightButtonManager.hpp"

class RightButtonBasic:public IrightButtonManager
{
    public:
    RightButtonBasic(std::vector<Button> &rightButtonsarg):IrightButtonManager(rightButtonsarg){}
    rightButtonState getRightButtonState() override;
};
