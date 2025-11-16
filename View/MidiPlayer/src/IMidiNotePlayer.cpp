#include "IMidiNotePlayer.hpp"

IMidiNotePlayer::IMidiNotePlayer(Model &model){
    model.addPlayObserver([this](const NotePlayInformation& n){
        this->updatePlayingNote(n);
    });
}