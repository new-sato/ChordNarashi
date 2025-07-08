#include "allClassManager.hpp"

void allClassManager::mainLoop()
{
    while(continueLoop)
    {
        chord_button_manager.updateState();
        rightButtonState right_button_state =right_button_manager.getRightButtonState();

        if(right_button_state.is_pressed)
        {
            if(!rightButtonHasPressed)
            {
                note_player.updateNote();
                time = 0.0;
                start = std::chrono::system_clock::now();
                rightButtonHasPressed = true;
            }
            else
            {
                end = std::chrono::system_clock::now();
                time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            }
            note_player.playNote(time);
        }
        else if(rightButtonHasPressed)
        {
            note_player.stopNote();
        }
    }
}
