#pragma once

#include <string>
#include <chrono>

#include "charaData.hpp"

/// @brief 画面中心を0とした時の位置。1を限界値としておこう
struct Location
{
    /// @brief 右方向を正とする
    double x;

    /// @brief 下方向を正とする
    double y;
};

class Idisplay
{
public:
    virtual void updateDisplay() = 0;
    /// @brief ✕ボタンが押されているか調べる
    /// @return 押されていたらtrue
    virtual bool is_x_button_pressed()=0;
    
    virtual void displayCharacter(const charaData&) = 0;
};
