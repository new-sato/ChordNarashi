#include "Controler.hpp"

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include "RtMidiNotePlayer.hpp"
#include "SDLManager.hpp"

#include "winButtonChecker.hpp"

int main(int argc, char *argv[])
{
    std::unique_ptr<StandardNotePlayer> hoge = std::make_unique<StandardNotePlayer>();
    Model model(
        std::make_unique<Chord2StandardNote>(),
        std::move(hoge)
    );
    

    RtMidiNotePlayer rtmnp(model);
    SDLManager sdlm;
    View view(rtmnp, sdlm, model);

    winButtonChecker w;
    Controler c(model, view, w);

    c.startLoop();
    return 0;
}
