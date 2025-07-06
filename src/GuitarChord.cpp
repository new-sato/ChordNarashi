#include "GuitarChord.hpp"



const std::vector<std::vector<note_set>> NoteTable{
    // C系コード
    {
        // Major
        {64, 60, 55, 52, 48},

        // minor
        {67, 63, 60, 55, 48}},

    // G
    {
        // Major
        {67, 59, 55, 50, 47, 43},

        // minor
        {67, 62, 58, 55, 50, 43},
    },

    // D
    {
        // Major
        {64, 62, 57, 50},

        // minor
        {65, 62, 57, 50}},

    // A
    {},

    // E
    {{}},

    // B
    {},

    // Fs

};

/// @brief 配下のbutton_2_chordが保持するchordネームから鳴らすべき音階を決定する。
void GuitarChord::generateNote()
{
    ChordName chord_name = button_2_cohord.getChordName();
    Notes = NoteTable[static_cast<int>(chord_name.root_note)][static_cast<int>(chord_name.chord_type)];
}
