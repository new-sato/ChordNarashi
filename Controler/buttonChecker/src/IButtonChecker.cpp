#include "IButtonChecker.hpp"

void IButtonChecker::checkButtons()
{
    updateChordButtons();
    updateShiftButtons();
    updateKeyButtons();
    updateModeButtons();
}

std::vector<bool> IButtonChecker::getKeyButtonState() const
{
    std::vector<bool> ans;
    for(int i=0;i<m_keyButtons.size();i++)
    {
        ans.push_back(m_keyButtons[i].getState());
    }
    return ans;
}
