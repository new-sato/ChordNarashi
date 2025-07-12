#include "ChordButtonManager.hpp"
#include "rightButtonBasic.hpp"
#include "InotePlayer.hpp"
#include "GuitarNotePlayer.hpp"
#include "SustainPedalManager.hpp"
#include "other_button.hpp"
#include "winButtonUpdater.hpp"

#include "rtmidi/RtMidi.h"

#include <chrono>

class allClassManager
{
    protected:
    std::vector<Button> chord_buttons = std::vector<Button>(NUM_OF_CHORD_BUTTON);
    std::vector<Button> shift_buttons = std::vector<Button>(static_cast<int>(Note::end));
    std::vector<OnceButton> key_buttons = std::vector<OnceButton>(static_cast<int>(keyButton::end));
    std::vector<Button> right_buttons = std::vector<Button>(static_cast<int>(rightButtonInfo::NUM_OF_BUTTON));
    std::vector<OnceButton> other_buttons = std::vector<OnceButton>(static_cast<int>(otherButton::NUM_OF_BUTTON));

    Button& sustain_button = *new Button;
    
    RtMidiOut midiOut;

    winButtonUpdater win_button_updater
        = winButtonUpdater(
            chord_buttons,
            shift_buttons,
            key_buttons,
            right_buttons,
            other_buttons,
            sustain_button
    );

    ChordButtonManager& chord_button_manager = *new ChordButtonManager(key_buttons, chord_buttons, shift_buttons);
    InotePlayer& note_player = *new GuitarNotePlayer(chord_button_manager, midiOut);
    IrightButtonManager& right_button_manager = *new RightButtonBasic(right_buttons);
    SustainPedalManager& sustain_pedal_manager = *new SustainPedalManager(sustain_button, midiOut);
    
    bool continueLoop = true;
    bool autoSustainPedal = true;
    bool rightButtonHasPressed = false ;
    double time_for_playNote;

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    
    std::chrono::system_clock::time_point loop_start = std::chrono::system_clock::now();
    
    public:
    allClassManager() = default;
    void setContinueLoop(bool arg) { continueLoop = arg; }
    void mainLoop();
};
