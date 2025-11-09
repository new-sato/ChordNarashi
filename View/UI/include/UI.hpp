#include "Idisplay.hpp"
#include "Block.hpp"

class UI
{
    Idisplay& m_display;
    
    std::vector<charaData> m_chara_data_to_display;
    std::vector<Block> m_blocks;
    
    void registCharacter();

public:
    UI(Idisplay& display);
    bool get_x_button_pressed()const{return m_display.is_x_button_pressed();}
    
    /// @brief UIの表示を更新する
    /// @param d_time 前回の更新からの経過時間　
    void updateUI(std::chrono::milliseconds d_time);
};
