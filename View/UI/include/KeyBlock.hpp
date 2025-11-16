#pragma once

#include "Block.hpp"
#include "Model.hpp"

#include <string>

class UI;

class KeyBlock:public Block
{
    const UI& m_ui;
    void changeKey(int input){m_key = input;}
    int m_key = 0;
public:
    KeyBlock(const UI&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
