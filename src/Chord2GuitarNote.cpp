#include "Chord2GuitarNote.hpp"
#include "map"

std::map<Note, int> RootMidiNums
{
    {Note::E,40},
    {Note::F,41},
    {Note::Fs,42},
    {Note::G,43},
    {Note::Af,44},
    {Note::A,45},
    {Note::Bf,46},
    {Note::B,47},
    {Note::C,48},
    {Note::Df,49},
    {Note::D,50},
    {Note::Ef,51},
};

std::map<ChordType,std::vector<std::set<int>>> chord_table
{
    {
        Major,
        {
            {0, 7, 12, 16, 19, 24},
            {0, 7, 12, 16, 19},
            {0, 4, 7, 12, 16}
        }
    },
    {
        minor,
        {
            {0, 7, 12, 15, 19, 24},
            {0, 7, 12, 15, 19},
            {0, 3, 7, 12, 15}
        }
    },
    {
        sev,
        {
            {0, 7, 12, 16, 19, 22},
            {0, 7, 10, 16, 19},
            {0, 4, 7, 10, 16}
        }
    },
    {
        Msev,
        {
            {0, 7, 12, 16, 19, 23},
            {0, 7, 11, 16, 19},
            {0, 4, 7, 11, 16}
        }
    },
    {
        msev,
        {
            {0, 7, 12, 15, 19, 22},
            {0, 7, 10, 15, 19},
            {0, 3, 7, 10, 15}
        }
    },
    {
        minor,
        {
            {0, 6, 12, 15, 18, 24},
            {0, 6, 12, 15, 18},
            {0, 3, 6, 12, 15}
        }
    },
    {
        arg,
        {
            {0, 8, 12, 16, 20, 24},
            {0, 8, 12, 16, 20},
            {0, 4, 8, 12, 16}
        }
    },
};

void Chord2GuitarNote::generateNote()
{
    button_2_cohord.updateChord();
    ChordName chord_name = button_2_cohord.getChordName();
    
    int root_midi_num = RootMidiNums[chord_name.root_note];

    if(root_midi_num<=42)
    {
        for(int i: chord_table[chord_name.chord_type][0])
        {
            Notes.insert(i+root_midi_num);
        }
    }
    else if(root_midi_num<=48)
    {
        for(int i: chord_table[chord_name.chord_type][1])
        {
            Notes.insert(i+root_midi_num);
        }
    }
    else
    {
        for(int i: chord_table[chord_name.chord_type][2])
        {
            Notes.insert(i+root_midi_num);
        }
    }
}