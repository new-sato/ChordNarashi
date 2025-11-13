#include "Idisplay.hpp"
#include "Block.hpp"
#include "Model.hpp"
#include <memory>

enum class KeySignatureMode{
    STANDARD,
    ALL_FLAT,
    ALL_SHARP
};


class UI
{
    Idisplay& m_display;
    
    std::vector<charaData> m_chara_data_to_display;
    std::vector<std::unique_ptr<Block>> m_blocks;

    KeySignatureMode m_key_signature_mode = KeySignatureMode::STANDARD;
    
    std::map<KeySignatureMode, std::vector<std::string>> m_key_str_table  =
    {
        {
            KeySignatureMode::STANDARD,
            {"C", "G", "D", "A", "E", "B", "F♯", "D♭", "A♭", "E♭", "B♭", "F"}
        },
        {
            KeySignatureMode::ALL_FLAT,
            {"C", "G", "D", "A", "E", "B", "G♭", "D♭", "A♭", "E♭", "B♭", "F"}
        },
        {
            KeySignatureMode::ALL_SHARP,
            {"C", "G", "D", "A", "E", "B", "F♯", "C♯", "G♯", "D♯", "A♯", "F"}
        }
    };

    void registCharacter();
    std::vector<std::string> m_key_str = m_key_str_table[KeySignatureMode::STANDARD];


public:
    UI(Idisplay& display, Model& model);
    bool get_x_button_pressed()const{return m_display.is_x_button_pressed();}
    
    const std::vector<std::string> get_key_str()const{return m_key_str;}
    
    std::string getChordNameStr(const ChordName&)const;
    
    void toggleSharpFlat();
    
    /// @brief UIの表示を更新する
    /// @param d_time 前回の更新からの経過時間　
    void updateUI(std::chrono::milliseconds d_time);
};
