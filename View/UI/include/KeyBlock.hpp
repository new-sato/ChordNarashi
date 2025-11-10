#include "Block.hpp"
#include "Model.hpp"

#include <string>

class KeyBlock:public Block
{
    const std::vector<std::string>& m_key_str;
    void changeKey(int input){m_key = input;}
    int m_key = 0;
public:
    KeyBlock(const std::vector<std::string>&, Model&);
    void updateBlock(std::chrono::milliseconds)override;
};
