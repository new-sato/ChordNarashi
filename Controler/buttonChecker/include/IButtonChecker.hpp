#pragma once

#include "Model.hpp"

class IButtonChecker
{
protected:
    bool has_ring_button_pressed;

    RealButtons m_real_buttons;


    virtual void updateChordButtons()=0;
    virtual void updateShiftButtons()=0;
    virtual void updateKeyButtons()=0;

    virtual void updateModeButtons()=0;
public:
    void checkButtons();
    const RealButtons& getChordRelatedButtons()const{return m_real_buttons;}
    virtual bool isRingButtonPressed() = 0;
    virtual bool isExitButtonPressed() = 0;
};
