#pragma once

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