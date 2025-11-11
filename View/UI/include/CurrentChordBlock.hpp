#pragma once
#include "Block.hpp"
#include "Model.hpp"

#include <string>

class CurrentChordBlock:public Block
{
    const std::vector<std::string>& m_key_str;
public:
    CurrentChordBlock(const std::vector<std::string>&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
