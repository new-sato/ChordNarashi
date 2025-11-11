#pragma once
#include "Block.hpp"
#include "Model.hpp"

#include <string>

class UI;

class CurrentChordBlock:public Block
{
    const UI& m_ui;
    void changeRingingChord(const ChordName&);
public:
    CurrentChordBlock(const UI&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
