#include "InotePlayer.hpp"

void InotePlayer::notifyPlaying(const NotePlayInformation& info)
{
    for(auto f:m_PlayObservers)
    {
        f(info);
    }
}

void InotePlayer::addPlayObserver(
    std::function<void(const NotePlayInformation &)> arg)
{
    m_PlayObservers.push_back(arg);
}
