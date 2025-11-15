#pragma once

struct Rectangle
{
    /// @brief 中心のx座標
    double x;

    /// @brief 中心のy座標
    double y;

    /// @brief 縦の辺の長さ
    double vertical_length;

    /// @brief 横の辺の長さ
    double horizontal_length;

    Rectangle(double x, double y, double v, double h);
};
