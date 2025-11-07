#include "Controler.hpp"

#include "Chord2StandardNote.hpp"
#include "StandardNotePlayer.hpp"

#include "RtMidiNotePlayer.hpp"

#include "winButtonChecker.hpp"

int main()
{
    std::unique_ptr<StandardNotePlayer> hoge = std::make_unique<StandardNotePlayer>();
    Model model(
        std::make_unique<Chord2StandardNote>(),
        std::move(hoge)
    );
    
    RtMidiNotePlayer rtmnp(model);
    View view(rtmnp);

    winButtonChecker w;
    
    Controler c(model, view, w);
    while(true)c.mainLoop();
}
