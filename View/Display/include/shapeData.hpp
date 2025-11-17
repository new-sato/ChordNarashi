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
    
    int red;
    int green;
    int blue;
    int alpha = 255;


    Rectangle(double x, double y, double v, double h ,int r, int g, int b);
};

struct Circle
{
    /// @brief 中心のx座標
    double x;

    /// @brief 中心のy座標
    double y;

    /// @brief 円の半径  
    double r;

    int red;
    int green;
    int blue;
    int alpha = 255;
};
