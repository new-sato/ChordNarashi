#include "keyButtonChecker.hpp"

int KeyButtonChecker::getKeyButtonState() const
{
    int ans=0;
    for(int i=0;i<static_cast<int>(keyButton::end);i++)
    {
        if(buttons[i].getIsPressed())
        {
            ans += keyButtonDiff[i];
        }
    }
    ans %= 12;
    return ans;
}
