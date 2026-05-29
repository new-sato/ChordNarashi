#include "Controler.hpp"

#include "noSustainTimingManager.hpp"
#include "SustainTimingManager.hpp"

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include "MiniaudioNotePlayer.hpp"
#include "SDLManager.hpp"

#include "SDLButtonChecker.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    Model model(
        std::make_unique<Chord2StandardNote>(),
        std::make_unique<StandardNotePlayer>(),
        std::make_unique<SustainTimingManager>()
    );
    

    MiniaudioNotePlayer rtmnp(model);
    SDLManager sdlm;
    model.addKeyObserver([&sdlm](int key){ sdlm.setKey(key); });
    
    View view(rtmnp, sdlm, model);

    SDLButtonChecker w(sdlm);
    Controler c(model, view, w);

    c.startLoop();
    return 0;
}

