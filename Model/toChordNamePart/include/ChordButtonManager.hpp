#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

#include <functional>

enum class ChordButtonType
{
    Major,
    minor,
    dim,
    arg,
    sus4,
    end
};


enum class Note
{
    C,
    G,
    D,
    A,
    E,
    B,
    Fs,
    Df,
    Af,
    Ef,
    Bf,
    F,
    end
};


// 本来は60
const int NUM_OF_CHORD_BUTTON = static_cast<int>(ChordButtonType::end) * static_cast<int>(Note::end);

const int NUM_OF_NOTE = static_cast<int>(Note::end);

struct RealButtons
{
    std::map<ChordButtonType, std::vector<bool>> buttons= {
        std::make_pair(ChordButtonType::Major, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::minor, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::dim, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::arg, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::sus4, std::vector<bool>(NUM_OF_NOTE, false))
    };

    std::vector<bool> keyButtons= std::vector<bool>(12,false);

    std::vector<bool> tempShihftButtons = std::vector<bool>(12,false);

    /// @brief すべてのボタンが離されているかどうか調べる
    /// @return すべてのボタンが離れていればtrue
    bool IsAllChordButtonReleased()const;
};

struct VirtualChordButton
{
    const ChordButtonType cbt;
    const Note note;

    VirtualChordButton(ChordButtonType type,Note n):cbt(type),note(n){}
    /// @brief 押されたボタンの番号と現在のキーを基に、どのコードに対応するかを決定
    /// @param button_num 押されているRealButtonの番号(0~11)
    /// @param key 現在のキー
    VirtualChordButton(ChordButtonType type, int button_num, int key);
    
    VirtualChordButton shift(unsigned int shift_diff);

    /// @brief mapのために必要
    /// @return 
    int ButtonNum() const;
    bool operator<(const VirtualChordButton& right) const {return this->ButtonNum() < right.ButtonNum();}
};

/// @brief 和音のボタンとキーマネージャーを配下に持ち、
/// ボタンの読み取り、ボタン押下の継続や記憶などを行い、
/// どのコードのボタンが押されたのかを特定する。
class ChordButtonManager
{
    std::set<VirtualChordButton> virtual_chord_buttons;
    
    int key = 0;
    int temp_shift = 0;

    /// @brief ぜ前回の更新時、コードぼボタンが押されていたかを見る
    bool no_button_has_been_pressed;
    
    /// @brief keyの監視をするやつを登録しておく
    std::vector<std::function<void(int)>> m_key_observer;
    void notify_key_change(int key)
    {
        for(auto func: m_key_observer)
        {
            func(key);
        }
    }

public:
    ChordButtonManager() = default;

    void update_state(const RealButtons& input);
    


    
    /// @brief キーを直接設定する。11以上なら12で割った剰余の番号のキーに設定される。ただし、キーの変更はコードボタンが押されていないときのみ行われる。
    /// @param new_key 新しいキーを正の整数で指定する。
    /// @return ずらした結果の番号を返す
    int setKey(unsigned int new_key);

    /// @brief 現在のキーを五度円の時計回り方向にずらす。
    /// @param key_diff 正の整数で、どれだけずらすかを指定する。
    /// @return ずらした結果の番号を返す
    int addKey(unsigned int key_diff)
    {
        return setKey(key + key_diff);
    }

    int getKey()const{ return key; }

    std::set<VirtualChordButton> getVirtualChordButtons()const;
    

    void addKeyObserver(std::function<void(int)> observer)
    {
        m_key_observer.push_back(observer);
    }
};