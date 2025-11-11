#include "Ichord2Note.hpp"

void Ichord2Note::notifyRingingChord(const ChordName &arg)
{
    for(auto func:m_ringing_chord_observer)
    {
        func(arg);
    }
}

NoteSet Ichord2Note::processNote(const ChordName &arg)
{
    notifyRingingChord(arg);
    return generateNote(arg);
}

void Ichord2Note::addRingingChordObserver(
    std::function<void(const ChordName &)> func)
{
    m_ringing_chord_observer.push_back(func);
}