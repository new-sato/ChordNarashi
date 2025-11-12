#include "Idisplay.hpp"
#include "Block.hpp"
#include "Model.hpp"
#include <memory>

class UI
{
    Idisplay& m_display;
    
    std::vector<charaData> m_chara_data_to_display;
    std::vector<std::unique_ptr<Block>> m_blocks;

    void registCharacter();
    std::vector<std::string> m_key_str = {"C", "G", "D", "A", "E", "B", "Fs", "Df", "Af", "Ef", "Bf", "F"};


public:
    UI(Idisplay& display, Model& model);
    bool get_x_button_pressed()const{return m_display.is_x_button_pressed();}
    
    const std::vector<std::string> get_key_str()const{return m_key_str;}
    
    std::string getChordNameStr(const ChordName&)const;
    
    /// @brief UIの表示を更新する
    /// @param d_time 前回の更新からの経過時間　
    void updateUI(std::chrono::milliseconds d_time);
};
