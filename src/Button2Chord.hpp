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
    ChordButtonManager& cbm;
    
    ChordName chord_name  = {0, Major, Note::C};

    void singleChord(std::set<VirtualChordButton> vec_of_chord);
    void doubleChord(std::set<VirtualChordButton> vec_of_chord);

public:
    Button2Chord(ChordButtonManager& arg):cbm(arg){};
    void updateChord();

    /// @brief 決定したコードネームを返す。
    /// @return 
    ChordName getChordName() { return chord_name; }
};