#pragma once

#include "IButtonChecker.hpp"
#include <windows.h>

class winButtonChecker:public IButtonChecker
{
    /// @brief キーボードのボタンがおされているかチェックする
    /// @param key 押されているかどうか確認するキーの番号
    /// @return キーが押されていればtrue
    bool checkButton(int key);
    
    void updateChordButtons()override;
    void updateShiftButtons()override;
    void updateKeyButtons()override;
    
    void updateModeButtons()override;
public:
    bool isRingButtonPressed()override;
    bool isSustainButtonPressed()override;
    bool isExitButtonPressed()override;
};
