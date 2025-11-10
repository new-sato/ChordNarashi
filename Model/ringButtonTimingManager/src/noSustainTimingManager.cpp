#include "noSustainTimingManager.hpp"

bool noSustainTimingManager::mustStopNote()
{
    if(is_button_NOW_released&&(!is_sustain_button_pressed))
    {
        return true;
    }
    else if(is_sustain_button_NOW_released&&(!is_button_pressed))
    {
        return true;
    }
    else return is_button_NOW_pressed;// 重複して複数のコードを鳴らさないように
}

bool noSustainTimingManager::mustStartNote()
{
    return is_button_NOW_pressed;
}

bool noSustainTimingManager::mustSustainNote(){
    return (is_button_pressed||is_sustain_button_pressed)&&(!is_button_NOW_pressed);
}
