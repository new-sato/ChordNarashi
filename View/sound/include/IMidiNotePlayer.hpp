#pragma once

#include "Model.hpp"

class IMidiNotePlayer
{
public:
    /// @brief NotePlayInformationの情報を基に、Midiの再生、停止を行う
    /// @param  
    virtual void playNote(const NotePlayInformation&) = 0;
};
