#include "InotePlayer.hpp"

InotePlayer::InotePlayer(Chord2Note& c2n):chord_2_note(c2n)
{
    
}

void InotePlayer::updateNote()
{
    chord_2_note.generateNote();
    note_to_play = chord_2_note.getNotes();
}