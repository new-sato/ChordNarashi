#include "Chord2StandardNote.hpp"
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
        dim,
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
    {
        sus4,
        {
            {0, 7, 12, 17, 19, 24},
            {0, 7, 12, 17, 19},
            {0, 5, 7, 12, 17}
        }
    },
    {
        mMsev,
        {
            {0, 7, 12, 15, 19, 23},
            {0, 7, 11, 15, 19},
            {0, 3, 7, 11, 15}
        }
    },
    {
        sevsus4,
        {
            {0, 7, 12, 17, 19, 22},
            {0, 7, 10, 17, 19},
            {0, 5, 7, 10, 17}
        }
    },
    {
        Msevsus4,
        {
            {0, 7, 12, 17, 19, 23},
            {0, 7, 11, 17, 19},
            {0, 5, 7, 11, 17}
        }
    },
    {
        add9,
        {
            {0, 7, 12, 16, 19, 26},
            {0, 4, 7, 12, 14, 19},
            {0, 4, 7, 12, 14}
        }
    },
};

NoteSet Chord2StandardNote::generateNote(const ChordName& chord_name)
{
    int root_midi_num = RootMidiNums[chord_name.root_note];

    NoteSet notes;

    if(root_midi_num<=42)
    {
        for(int i: chord_table[chord_name.chord_type][0])
        {
            notes.insert(i+root_midi_num);
        }
    }
    else if(root_midi_num<=47)
    {
        for(int i: chord_table[chord_name.chord_type][1])
        {
            notes.insert(i+root_midi_num);
        }
    }
    else
    {
        for(int i: chord_table[chord_name.chord_type][2])
        {
            notes.insert(i+root_midi_num);
        }
    }

    return notes;
}