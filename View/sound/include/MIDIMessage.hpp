#pragma once
#include "Model.hpp"

using MidiChannelNum = unsigned char;

/// @brief ノートの再生、停止に必要な情報をまとめる
struct MidiMessage
{
    MidiChannelNum midi_channel_num;
    
    /// @brief 構造体からメッセージのビット列を作成
    /// @return 
    virtual std::vector<unsigned char> message()const = 0;
};

struct MidiNoteOnMessage: public MidiMessage
{
    MidiNoteNum note_number;
    unsigned char velocity;

    MidiNoteOnMessage(
        MidiNoteNum note_number_arg,
        unsigned char velocity_arg=100
    ):note_number(note_number), velocity(velocity_arg){};
    
    std::vector<unsigned char> message() const;
};

struct MidiNoteOffMessage: public MidiMessage
{
    MidiNoteNum note_number;
    unsigned char velocity;

    MidiNoteOffMessage(
        MidiNoteNum note_number_arg,
        unsigned char velocity_arg=100
    ):note_number(note_number), velocity(velocity_arg){};
    std::vector<unsigned char> message() const;
};
