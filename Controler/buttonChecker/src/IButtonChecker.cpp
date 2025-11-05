#include "IButtonChecker.hpp"

void IButtonChecker::checkButtons()
{
    updateChordButtons();
    updateShiftButtons();
    updateKeyButtons();
    updateModeButtons();
}
