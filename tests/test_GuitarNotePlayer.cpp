#include <gtest/gtest.h>
#include "GuitarNotePlayer.hpp"

class GuitarNoteTest: public testing::Test
{
    protected:
    std::vector<Button> ChordButtons = std::vector<Button>(NUM_OF_CHORD_BUTTON);
    std::vector<OnceButton> KeyButton = std::vector<OnceButton>(static_cast<int>(keyButton::end));
    ChordButtonManager c= ChordButtonManager(KeyButton, ChordButtons);
    GuitarNotePlayer player = GuitarNotePlayer(c);
    virtual void SetUp(){};
};

TEST_F(GuitarNoteTest, init)
{
    ChordButtons[1].setIsPressed(true);
    c.update_vcb_state();
    player.updateNote();
    player.playNote(0.0);
    player.stopNote();
    ChordButtons[1].setIsPressed(false);
    c.update_vcb_state();
    ChordButtons[0].setIsPressed(true);
    c.update_vcb_state();
    player.updateNote();
    player.playNote(0.0);
    player.stopNote();
}
