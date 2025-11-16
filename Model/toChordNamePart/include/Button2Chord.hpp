#pragma once

#include "ChordButtonManager.hpp"
#include <set>

// Cmから見ると、Cは3つ右回りに進んだところにある
const int MIN_DIFF = 3;

// Cdimから見ると、CMは5こ先に行ったところにある
const int DIM_DIFF = 5;

/// @brief 鳴らすべきコードの種類
enum ChordType
{
    Major,
    minor,
    dim,
    arg,
    sus4,
    sev,
    Msev,
    msev,
    mMsev,
    dimsev,
    argsev,
    sevsus4,
    Msevsus4,
    add9,
    end
};

/// @brief 最終的に決定したコードネーム
struct ChordName
{
    /// @brief 0でコード
    int flag;
    ChordType chord_type;
    Note root_note;
};

/// @brief 受け取ったバーチャルボタンの入力から、コードネーム（CM7など）を決定する。
class Button2Chord
{
    
    ChordName m_chord_name  = {0, Major, Note::C};
    
    std::vector<std::function<void(const ChordName&)>> m_current_chord_observer;

    void singleChord(const std::set<VirtualChordButton>& vec_of_chord);
    void doubleChord(const std::set<VirtualChordButton>& vec_of_chord);
    
    void notifyCurrentChord(const ChordName&);

public:
    Button2Chord(){};
    void updateChord(const std::set<VirtualChordButton>& pressed_button);
    
    void addCurrentChordObserver(std::function<void(ChordName)>);

    /// @brief 決定したコードネームへの参照を返す。
    /// @return const ChordName&型
    const ChordName& getChordName()const{ return m_chord_name; }
};