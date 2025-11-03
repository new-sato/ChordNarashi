#include "StandardNotePlayer.hpp"
#include <exception>

void StandardNotePlayer::playNote(float time)
{
    if(time == 0)
    {
        notifyPlaying(NotePlayInformation(m_note_to_play, {}, {}));
        m_note_played = m_note_to_play;
        m_note_to_play.clear();
    }
    else if(time > 0)
    {
        notifyPlaying(NotePlayInformation({}, m_note_played, {}));
    }

}

void StandardNotePlayer::stopNote()
{
    notifyPlaying(NotePlayInformation({}, {}, m_note_played));
}
