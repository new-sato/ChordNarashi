#include "GuitarChord.hpp"



const std::vector<std::vector<note_set>> NoteTable{
    // C系コード
    {
        // Major
        {64, 60, 55, 52, 48},

        // minor
        {68, 63, 60, 55, 48},
    
        //dim
        {62,58,52,46},

        //arg
        {61,56,52,48},

        //sus4
        {},

        //sev
        {}

        //Msev

        //msev
    },


    // G
    {
        // Major
        {62, 59, 55, 50, 47, 43},

        // minor
        {62, 58, 55, 50, 43},
    },

    // D
    {
        // Major
        {66, 62, 57, 50},

        // minor
        {65, 62, 57, 50}},

    // A
    {
        // Major
        {64,61,57,52,45},

        // minor
        {64, 60, 57, 52, 45}
    },

    // E
    {
        // Major
        {64,59,56,52,47,40},
        
        // minor
        {64,59,55,52,47,40}
    },

    // B
    {
        //M
        {63,59,54,51,47},
        //m
        {62,59,54,50,47},
        //dim
        {61,52,46,42}
    },

    // Fs
    {
        //M
        {42,49,54,58,61},
        {42,49,54,57,61}
    },

    // Df
    {
        //M
        {49,53,56,61,65},
        {49,56,61,64,67},
    },

    // Af
    {
        {44, 51, 56, 60, 63},
        {44, 51, 56, 59, 63},
    },

    // Ef
    {
        {51, 55, 58, 63, 67},
        {51, 54, 58, 63, 66}
    },

    // Bf
    {
        {46, 53, 58, 62, 65},
        {46, 53, 58, 61, 65}
    },

    //F
    {
        // major
        {65,60,57,53,48,41},

        // minor
        {63,60,56,53,48,41}
    }
};

/// @brief 配下のbutton_3_chordが保持するchordネームから鳴らすべき音階を決定する。
void GuitarChord::generateNote()
{
    button_2_cohord.updateChord();
    ChordName chord_name = button_2_cohord.getChordName();
    Notes = NoteTable[static_cast<int>(chord_name.root_note)][static_cast<int>(chord_name.chord_type)];
}
