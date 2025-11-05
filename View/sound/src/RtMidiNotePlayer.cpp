#include "RtMidiNotePlayer.hpp"

RtMidiNotePlayer::RtMidiNotePlayer(Model& model)
{
    init();
    model.addPlayObserver
    (
        [this](const NotePlayInformation& arg)
        {
            this->updatePlayingNote(arg);
        }
    );
}

void RtMidiNotePlayer::init()
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


void RtMidiNotePlayer::updatePlayingNote(
    const NotePlayInformation &note_play_info)
{
    for(MidiNoteNum to_start: note_play_info.note_to_start)
    {
        MidiNoteOnMessage start_message(to_start);
        midiOut.sendMessage(&start_message.message());
    }
    
    for(MidiNoteNum to_end: note_play_info.note_to_end)
    {
        MidiNoteOffMessage end_message(to_end);
        midiOut.sendMessage(&end_message.message());
    }
}
