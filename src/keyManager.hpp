#pragma once

#include <vector>
#include "ChordButtonManager.hpp"

class ChordButtonManager;

class KeyManager
{
    // Cを0として、五度円を右回りに、最大でFの11
    int key = 0;

    ChordButtonManager &cbm;

    public:

    KeyManager(ChordButtonManager& c):cbm(c){}
    
    int getKey()const{return key;}

    /// @brief キーを直接設定する。11以上なら12で割った剰余の番号のキーに設定される。ただし、キーの変更はコードボタンが押されていないときのみ行われる。
    /// @param new_key 新しいキーを正の整数で指定する。
    void setKey(unsigned int new_key);

    /// @brief 現在のキーを五度円の時計回り方向にずらす。
    /// @param key_diff 正の整数で、どれだけずらすかを指定する。
    void addKey(unsigned int key_diff){ setKey(key + key_diff); }
    
};
