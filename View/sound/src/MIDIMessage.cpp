#include "MIDIMessage.hpp"

std::vector<unsigned char> MidiNoteOnMessage::message()const
{
    std::vector<unsigned char> ans;
    const unsigned char NOTE_ON_MESSAGE = 0x90;
    
    ans.push_back(NOTE_ON_MESSAGE + midi_channel_num);
    ans.push_back(note_number);
    ans.push_back(velocity);

    return ans;
}

std::vector<unsigned char> MidiNoteOffMessage::message()const
{
    std::vector<unsigned char> ans;
    const unsigned char NOTE_ON_MESSAGE = 0x80;
    
    ans.push_back(NOTE_ON_MESSAGE + midi_channel_num);
    ans.push_back(note_number);
    ans.push_back(velocity);

    return ans;
}
