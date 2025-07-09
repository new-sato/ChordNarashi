#include "allClassManager.hpp"

void allClassManager::mainLoop()
{
    while(continueLoop)
    {

        while(
            [=]() -> bool
            {
                auto now_time = std::chrono::system_clock::now();
                auto d_time = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - loop_start).count();
                return (d_time < 5);
            }()
        );
        
        loop_start = std::chrono::system_clock::now();

        win_button_updater.updateAllButtons();
        
        if(other_buttons[static_cast<int>(otherButton::EXIT)].getIsPressed() == true)
            break;
        
        if(other_buttons[static_cast<int>(otherButton::TUGGLE_STROKE)].getIsPressed() == true)
        {
            static_cast<GuitarNotePlayer&>(note_player).tuggleStroke();
        }

        chord_button_manager.updateState();
        rightButtonState right_button_state =right_button_manager.getRightButtonState();

        if(right_button_state.is_pressed)
        {
            if(!rightButtonHasPressed)
            {
                note_player.updateNote();
                time_for_playNote = 0.0;
                start = std::chrono::system_clock::now();
                rightButtonHasPressed = true;
            }
            else
            {
                end = std::chrono::system_clock::now();
                time_for_playNote = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            }
            note_player.playNote(time_for_playNote);
        }
        else if(rightButtonHasPressed)
        {
            note_player.stopNote();
            rightButtonHasPressed = false;
        }
    }
}
