#include "InotePlayer.hpp"

void InotePlayer::notifyPlaying(const NotePlayInformation& info)
{
    for(auto f:m_PlayObservers)
    {
        f(info);
    }
}
