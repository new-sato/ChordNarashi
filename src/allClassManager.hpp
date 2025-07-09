#include "ChordButtonManager.hpp"
#include "rightButtonBasic.hpp"
#include "InotePlayer.hpp"
#include "GuitarNotePlayer.hpp"

#include <chrono>

class allClassManager
{
    protected:
    std::vector<Button> chord_buttons = std::vector<Button>(NUM_OF_CHORD_BUTTON);
    std::vector<Button> shift_buttons = std::vector<Button>(Note::end);
    std::vector<OnceButton> key_buttons = std::vector<OnceButton>(static_cast<int>(keyButton::end));
    std::vector<Button> right_buttons = std::vector<Button>(rightButtonInfo::NUM_OF_BUTTON);

    ChordButtonManager& chord_button_manager = *new ChordButtonManager(key_buttons, chord_buttons, shift_buttons);
    InotePlayer& note_player = *new GuitarNotePlayer(chord_button_manager);
    IrightButtonManager& right_button_manager = *new RightButtonBasic(right_buttons);
    bool continueLoop = true;

    bool rightButtonHasPressed = false ;
    double time;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    
    
    public:
    allClassManager();
    void setContinueLoop(bool arg) { continueLoop = arg; }
    void mainLoop();
};
