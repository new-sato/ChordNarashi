#pragma once

#include <chrono>

class Idisplay
{
public:
    virtual void updateDisplay() = 0;
    /// @brief ✕ボタンが押されているか調べる
    /// @return 押されていたらtrue
    virtual bool is_x_button_pressed()=0;
};
