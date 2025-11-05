#include "Controler.hpp"

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include "RtMidiNotePlayer.hpp"

#include "winButtonChecker.hpp"

int main()
{
    Model model(
        std::make_unique<Chord2StandardNote>(),
        std::make_unique<StandardNotePlayer>()
    );
    
    RtMidiNotePlayer rtmnp(model);
    View view(rtmnp);

    winButtonChecker w;
    
    Controler c(model, view, w);
    c.mainLoop();
}
