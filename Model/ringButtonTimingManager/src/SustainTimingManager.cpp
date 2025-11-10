#include "SustainTimingManager.hpp"

bool SustainTimingManager::mustStopNote()
{
    return is_button_NOW_pressed;
}

bool SustainTimingManager::mustStartNote()
{
    return is_button_NOW_pressed;
}

bool SustainTimingManager::mustSustainNote(){
    return is_button_NOW_pressed;
}
