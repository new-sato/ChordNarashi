#include "noSustainTimingManager.hpp"

bool noSustainTimingManager::mustStopNote()
{
    return is_button_NOW_released;
}

bool noSustainTimingManager::mustStartNote()
{
    return is_button_NOW_pressed;
}

bool noSustainTimingManager::mustSustainNote(){
    return is_button_pressed&&(!is_button_NOW_pressed);
}
