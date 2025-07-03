#include "button.hpp"
#include <vector>

// 本来は60
const int NUM_OF_CHORD_BUTTON = 6;

class ChordButtonManager
{
    std::vector<Button> real_chord_buttons;
    std::vector<bool> virtual_chord_buttons;
    
    bool no_button_has_been_pressed;
    
    public:
    ChordButtonManager();
    void update_vcb_state();
    bool is_all_button_releaced();

    std::vector<bool> getVirtualChordButtons()const{return virtual_chord_buttons;}

    void setButtonState(int n, bool state){real_chord_buttons[n].setIsPressed(state);}
};