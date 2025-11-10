#include "IringButtonTimingManager.hpp"

class noSustainTimingManager:IringButtonTimingManager
{
public:
    noSustainTimingManager() = default;
    bool mustStopNote()override;
    bool mustStartNote()override;
    bool mustSustainNote()override;
};
