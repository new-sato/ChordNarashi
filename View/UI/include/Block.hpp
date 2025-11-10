#pragma once
#include<vector>
#include <chrono>
#include "charaData.hpp"
#include "charaDataInBlock.hpp"

/// @brief 表示するエリアの一部分
class Block
{
protected:
    /// @brief ウィンドウ全体から見た時の幅
    double base_size;

    /// @brief ブロックの縦横比
    double ratio = 1.0;
    double x;
    double y;
    
    //TODO テスト用　後で治す
    std::vector<charaDataInBlock> m_chara_to_display;

public:
    virtual void updateBlock(std::chrono::milliseconds){return;};
    
    /// @brief 
    /// @param base_size ウィンドウ全体から見た時の幅(0~2)
    /// @param x ウィンドウ全体においての中心のx座標の位置(-1~1)
    /// @param y ウィンドウ全体においての中心のy座標の位置(-1~1)
    Block(
        double base_size_arg,
        double ratio_arg,
        double x_arg,
        double y_arg
    ):
        base_size(base_size_arg),
        ratio(ratio_arg),
        x(x_arg),
        y(y_arg)
    {}
    
    /// @brief 座標変換を行ってから自分が持っているデータを返す
    /// @return 座標変換を行った後の文字データ
    std::vector<charaData> getCharaToDisplay() const;
};