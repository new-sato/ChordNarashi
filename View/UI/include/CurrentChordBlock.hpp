#pragma once
#include "Block.hpp"
#include "Model.hpp"

#include <string>

class UI;

class CurrentChordBlock:public Block
{
    const UI& m_ui;

    std::string m_ringing_chord_name;
    void setRingingChordName(const ChordName&);

    void changeRingingChord(const ChordName&);
public:
    CurrentChordBlock(const UI&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
