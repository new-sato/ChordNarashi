#pragma once
#include <string>

/// @brief ブロックの中で用いる型
struct charaDataInBlock
{
    /// @brief 中心のx座標
    double x;

    /// @brief 中心のy座標
    double y;
    
    /// @brief フォントサイズ
    int font_size;
    
    /// @brief 表示したい文字列
    std::string str;
    
    charaDataInBlock(
        double x_arg,
        double y_arg,
        int font_size_arg,
        std::string str_arg
    ):x(x_arg), y(y_arg), font_size(font_size_arg), str(str_arg){}
};