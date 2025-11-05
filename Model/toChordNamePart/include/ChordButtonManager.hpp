#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <functional>

#include "VirtualChordButton.hpp"

struct RealButtons
{
    std::map<ChordButtonType, std::vector<bool>> chordButtons= {
        std::make_pair(ChordButtonType::Major, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::minor, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::dim, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::arg, std::vector<bool>(NUM_OF_NOTE, false)),
        std::make_pair(ChordButtonType::sus4, std::vector<bool>(NUM_OF_NOTE, false))
    };

    std::vector<bool> tempShihftButtons = std::vector<bool>(12,false);

    /// @brief すべてのボタンが離されているかどうか調べる
    /// @return すべてのボタンが離れていればtrue
    bool IsAllChordButtonReleased()const;
};


/// @brief 和音のボタンとキーマネージャーを配下に持ち、
/// ボタンの読み取り、ボタン押下の継続や記憶などを行い、
/// どのコードのボタンが押されたのかを特定する。
// TODO 名前要検討
// コードボタンとキーの折衝を行う役割なので、そういう感じの名前にしたい。
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

    /// @brief 現在のキーを五度円の時計回り方向にずらす。コードボタンが押されいるときは効果がない。
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