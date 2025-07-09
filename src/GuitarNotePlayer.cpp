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

void GuitarNotePlayer::playNoteStroke(float time)
{
    if(time == 0.0)
    {
        auto now_time = std::chrono::system_clock::now();
        double deltaTime = 
            std::chrono::duration_cast<std::chrono::milliseconds>(now_time -prevPlayPoint).count();
        
        if (deltaTime > 150)
        {
            DownStrawk = true;
        }
        else
        {
            DownStrawk = (DownStrawk)?false:true;
        }
        prevPlayPoint = now_time;
    }

    if(DownStrawk){playNoteDownStroke(time);}
    else {playNoteUpStroke(time);}
}

void GuitarNotePlayer::playNoteDownStroke(float time)
{
    static double t;
    if(time==0.0)
    {
        t = 0;
        int hoge = *note_to_play.begin();
        std::vector<unsigned char> noteOnMsg={0x90, static_cast<unsigned char>(hoge), 100};
        midiOut.sendMessage(&noteOnMsg);
        note_played.insert(hoge);
        note_to_play.erase(note_to_play.begin());
    }
    else if(!note_to_play.empty() && time - t > 10)
    {
        t=time;
        int hoge = *note_to_play.begin();
        std::vector<unsigned char> noteOnMsg={0x90, static_cast<unsigned char>(hoge), 100};
        midiOut.sendMessage(&noteOnMsg);
        note_played.insert(hoge);
        note_to_play.erase(note_to_play.begin());
    }
}

void GuitarNotePlayer::playNoteUpStroke(float time)
{
    static double t;
    if(time==0.0)
    {
        t = 0;
        int hoge = *(--note_to_play.end());
        std::vector<unsigned char> noteOnMsg={0x90, static_cast<unsigned char>(hoge), 100};
        midiOut.sendMessage(&noteOnMsg);
        note_played.insert(hoge);
        note_to_play.erase(--note_to_play.end());
    }
    else if(!note_to_play.empty() && time - t > 10)
    {
        t=time;
        int hoge = *(--note_to_play.end());
        std::vector<unsigned char> noteOnMsg={0x90, static_cast<unsigned char>(hoge), 100};
        midiOut.sendMessage(&noteOnMsg);
        note_played.insert(hoge);
        note_to_play.erase(--note_to_play.end());
    }

}

void GuitarNotePlayer::playNoteStraight(float time)
{
    if(time == 0.0)
    {
        for(int n: note_to_play)
        {
            std::vector<unsigned char> noteOnMsg = {0x90, static_cast<unsigned char>(n), 100};
            midiOut.sendMessage(&noteOnMsg);
        }
        note_played = note_to_play;
        note_to_play.clear();
    }
}

GuitarNotePlayer::GuitarNotePlayer(Chord2GuitarNote& gc):InotePlayer(gc)
{
    init();
}

GuitarNotePlayer::GuitarNotePlayer(ChordButtonManager& cbm):GuitarNotePlayer(*new Chord2GuitarNote(cbm)){}

void GuitarNotePlayer::playNote(float time)
{
    if(do_stroke)
    {
        playNoteStroke(time);
    }
    else
    {
        playNoteStraight(time);
    }
}

void GuitarNotePlayer::stopNote()
{
    for(int n: note_played)
    {
        std::vector<unsigned char> noteOnMsg = {0x80, static_cast<unsigned char>(n), 0};
        midiOut.sendMessage(&noteOnMsg);
    }
    note_to_play.clear();
    note_played.clear();
}
