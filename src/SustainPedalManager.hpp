#pragma once
#include "button.hpp"
#include "rtmidi/RtMidi.h"

class SustainPedalManager
{
    Button& button;
    
    // RtMidiOutの初期化はほかの場所(Playerなど)で行うものとする
    RtMidiOut& rt_midi_out;
    bool hasPedalPressed = false;
    
    /// @brief ボタンが押されていない状態でのサステインの状態を表す
    bool default_state = false;

    public:
    SustainPedalManager(Button & b, RtMidiOut& rtmidiout): button(b), rt_midi_out(rtmidiout){}
    ~SustainPedalManager(){sendPedalMessage(false);}
    void toggleDefaultState();
    void sustainPedalProcess();
    void sendPedalMessage(bool isPedalPressed);
};