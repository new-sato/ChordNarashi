#pragma once

#include "Block.hpp"
#include "Model.hpp"

class UI;

class CurrentPressedChordBlock: public Block
{
    const UI& m_ui;
    void updateCurrentChord(const ChordName&);
    ChordName m_current_chord;
    
public:
    CurrentPressedChordBlock(const UI&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
