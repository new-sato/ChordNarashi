#pragma once
#include "IringButtonTimingManager.hpp"

class SustainTimingManager:public IringButtonTimingManager
{
public:
    SustainTimingManager() = default;
    bool mustStopNote()override;
    bool mustStartNote()override;
    bool mustSustainNote()override;
};
