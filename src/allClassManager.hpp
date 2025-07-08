#include "ChordButtonManager.hpp"
#include "IrightButtonManager.hpp"
#include "InotePlayer.hpp"
#include "GuitarNotePlayer.hpp"

#include <chrono>

class allClassManager
{
    std::vector<Button> chord_buttons = std::vector<Button>(NUM_OF_CHORD_BUTTON);
    std::vector<OnceButton> key_buttons = std::vector<OnceButton>(static_cast<int>(keyButton::end));
    //HACK 多様な数の右手ボタンに対応できるようにする
    std::vector<Button> right_buttons = std::vector<Button>(1);


    ChordButtonManager& chord_button_manager = *new ChordButtonManager(key_buttons, chord_buttons);
    InotePlayer& note_player = *new GuitarNotePlayer(chord_button_manager);
    IrightButtonManager& right_button_manager;
    bool continueLoop = true;

    bool rightButtonHasPressed = false ;
    double time;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    public:
    allClassManager();
    void mainLoop();
};
