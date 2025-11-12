#pragma once

#include "Model.hpp"
#include "OnceButton.hpp"

class IButtonChecker
{
protected:
    bool has_ring_button_pressed;

    RealButtons m_real_buttons;

    std::vector<OnceButton> m_keyButtons = std::vector<OnceButton>(12);

    

    virtual void updateChordButtons()=0;
    virtual void updateShiftButtons()=0;
    virtual void updateKeyButtons()=0;

    virtual void updateModeButtons()=0;
public:
    void checkButtons();
    
    const RealButtons& getChordRelatedButtons()const{return m_real_buttons;}
    std::vector<bool> getKeyButtonState()const;

    virtual bool isRingButtonPressed() = 0;
    virtual bool isSustainButtonPressed() = 0;
    virtual bool isExitButtonPressed() = 0;
};
