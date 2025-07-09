#include "GuitarNotePlayer.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

void GuitarNotePlayer::init()
{
    try
    {
        // 利用可能なMIDI出力ポートを調べる
        unsigned int nPorts = midiOut.getPortCount();
        if (nPorts == 0)
        {
            std::cout << "利用可能なMIDI出力ポートがありません" << std::endl;
            throw(0);
        }

        // loopMIDIで作成したポートを探す
        std::string port_name;
        int port_number =-1;
        for (unsigned int i = 0; i < nPorts; i++)
        {
            port_name = midiOut.getPortName(i);
            std::cout << port_name << std::endl;
            if(port_name.find("loopMIDI") != std::string::npos)
            {
                port_number = i;
                break;
            }
        }
        
        if (port_number == -1)
        {
            std::cout << "loopMIDIポートが見つかりませんでした。"<<std::endl;
        }
        
        // ポートを開く
        midiOut.openPort(port_number);
        std::cout << midiOut.getPortName(port_number) <<"に接続しました。" << std::endl;
    }
    catch(int)
    {
        std::cout << "MIDIポートの作成に失敗しました。" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

GuitarNotePlayer::GuitarNotePlayer(Chord2GuitarNote& gc):InotePlayer(gc)
{
    init();
}

GuitarNotePlayer::GuitarNotePlayer(ChordButtonManager& cbm):GuitarNotePlayer(*new Chord2GuitarNote(cbm)){}

void GuitarNotePlayer::playNote(float time)
{
    if(time == 0.0)
    {
        for(int n: note_to_play)
        {
            std::vector<unsigned char> noteOnMsg = {0x90, static_cast<unsigned char>(n), 100};
            midiOut.sendMessage(&noteOnMsg);
        }
    }
}

void GuitarNotePlayer::stopNote()
{
    for(int n: note_to_play)
    {
        std::vector<unsigned char> noteOnMsg = {0x80, static_cast<unsigned char>(n), 0};
        midiOut.sendMessage(&noteOnMsg);
    }
}
