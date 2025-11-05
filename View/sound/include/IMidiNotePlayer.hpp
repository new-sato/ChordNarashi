#pragma once

#include "Model.hpp"
#include "MIDIMessage.hpp"

class IMidiNotePlayer
{
public:
    /// @brief NotePlayInformationの情報を基に、Midiの再生、停止を行う
    /// @param  
    virtual void updatePlayingNote(const NotePlayInformation&) = 0;
    IMidiNotePlayer(Model&);
    
};
