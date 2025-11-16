#include "KeyBlock.hpp"
#include "UI.hpp"

using namespace std;

KeyBlock::KeyBlock(const UI& ui, Model& model):
    Block(1.0, 1.0, 0, 0), m_ui(ui)
{
    model.addKeyObserver([this](int key){this->changeKey(key);});  
}

void KeyBlock::updateBlock(std::chrono::milliseconds)
{
    m_chara_to_display.clear();
    m_chara_to_display.push_back(charaDataInBlock(0, 0, 24, m_ui.get_key_str()[m_key]));
}
