#include "IringButtonTimingManager.hpp"

class noSustainTimingManager:IringButtonTimingManager
{
public:
    bool mustStopNote()override;
    bool mustStartNote()override;
};
