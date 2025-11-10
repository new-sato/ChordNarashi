#include "Controler.hpp"

#include "noSustainTimingManager.hpp"

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include "RtMidiNotePlayer.hpp"
#include "SDLManager.hpp"

#include "winButtonChecker.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    Model model(
        std::make_unique<Chord2StandardNote>(),
        std::make_unique<StandardNotePlayer>(),
        std::make_unique<noSustainTimingManager>()
    );
    

    RtMidiNotePlayer rtmnp(model);
    SDLManager sdlm;
    View view(rtmnp, sdlm);

    winButtonChecker w;
    Controler c(model, view, w);

    c.startLoop();
    return 0;
}
