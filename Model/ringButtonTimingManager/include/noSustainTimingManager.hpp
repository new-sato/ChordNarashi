#pragma once
#include "IringButtonTimingManager.hpp"

class noSustainTimingManager:public IringButtonTimingManager
{
public:
    noSustainTimingManager() = default;
    bool mustStopNote()override;
    bool mustStartNote()override;
    bool mustSustainNote()override;
};
