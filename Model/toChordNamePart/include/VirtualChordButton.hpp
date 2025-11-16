#pragma once

#include "enum_constant.hpp"

struct VirtualChordButton
{
    const ChordButtonType cbt;
    const Note note;

    VirtualChordButton(ChordButtonType type,Note n):cbt(type),note(n){}
    /// @brief 押されたボタンの番号と現在のキーを基に、どのコードに対応するかを決定
    /// @param button_num 押されているRealButtonの番号(0~11)
    /// @param key 現在のキー
    VirtualChordButton(ChordButtonType type, int button_num, int key);
    
    VirtualChordButton shift(unsigned int shift_diff);

    /// @brief mapのために必要
    /// @return 
    int ButtonNum() const;
    bool operator<(const VirtualChordButton& right) const {return this->ButtonNum() < right.ButtonNum();}
};