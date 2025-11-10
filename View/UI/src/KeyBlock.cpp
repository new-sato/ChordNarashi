#include "KeyBlock.hpp"

using namespace std;

KeyBlock::KeyBlock(const vector<string>& key_str, Model& model):
    Block(1.0, 1.0, 0, 0), m_key_str(key_str)
{
    model.addKeyObserver([this](int key){this->changeKey(key);});  
}

void KeyBlock::updateBlock(std::chrono::milliseconds)
{
    m_chara_to_display.clear();
    m_chara_to_display.push_back(charaDataInBlock(0, 0, 24, m_key_str[m_key]));
}
