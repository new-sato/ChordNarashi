#include "SustainPedalManager.hpp"
#include <vector>

void SustainPedalManager::toggleDefaultState()
{
    if(default_state == true){
        default_state = false;
    }else{
        default_state = true;
    }
}

void SustainPedalManager::sustainPedalProcess()
{
    // ペダルが踏まれている状態のとき
    if(button.getIsPressed() != default_state)
    {
        // 押されっぱなしのときは何もしなくていい
        if(hasPedalPressed) return;

        //初めて押された場合
        hasPedalPressed = true;
        std::vector<unsigned char> noteOnMsg = {0xB0, static_cast<unsigned char>(64), 0x7F};
        rt_midi_out.sendMessage(&noteOnMsg);
    }
    // ボタンが押されてないとき
    else
    {
        // 放されっぱなしのときは何もしなくていい
        if(!hasPedalPressed) return;

        //初めて放されたとき
        hasPedalPressed = false;
        std::vector<unsigned char> noteOnMsg = {0xB0, static_cast<unsigned char>(64), 0x00};
        rt_midi_out.sendMessage(&noteOnMsg);
    }
}