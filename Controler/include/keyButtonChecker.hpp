#pragma once

#include "oncebutton.hpp"
#include <vector>

enum class keyButton
{
    Dominant,
    Subdominant,
    SemitoneUp,
    SemitoneDown,
    end
};

class KeyButtonChecker
{
    std::vector<OnceButton> &buttons;
    //HACK
    const std::vector<int> keyButtonDiff{1,11,7,5};
    
    public:
    KeyButtonChecker(std::vector<OnceButton>& arg):buttons(arg){}
    int getKeyButtonState() const;
};
