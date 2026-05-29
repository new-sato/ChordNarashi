#pragma once

#include "IButtonChecker.hpp"
#include "Idisplay.hpp"
#include <SDL3/SDL_scancode.h>

class SDLButtonChecker : public IButtonChecker
{
    Idisplay& m_display;

    bool checkButton(SDL_Scancode key);

    void updateChordButtons() override;
    void updateShiftButtons() override;
    void updateKeyButtons() override;
    void updateModeButtons() override;

public:
    SDLButtonChecker(Idisplay& display);

    bool isRingButtonPressed() override;
    bool isSustainButtonPressed() override;
    bool isExitButtonPressed() override;
};
