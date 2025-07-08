#include <gtest/gtest.h>
#include "GuitarChord.hpp"

class GuitarChordTest: public testing::Test
{
    protected:
    std::vector<Button> ChordButtons = std::vector<Button>(NUM_OF_CHORD_BUTTON);
    std::vector<OnceButton> KeyButton = std::vector<OnceButton>(static_cast<int>(keyButton::end));
    ChordButtonManager c= ChordButtonManager(KeyButton, ChordButtons);
    Button2Chord fuga=Button2Chord(c);
    GuitarChord piyo = GuitarChord(fuga);
    virtual void SetUp(){
    }
};

TEST_F(GuitarChordTest, C)
{   
    c.setRealButtonState(0, true);
    c.update_vcb_state();
    fuga.updateChord();
    piyo.generateNote();

    auto ans = note_set{64, 60, 55, 52,48};
    
    EXPECT_EQ(ans,piyo.getNotes());
}

TEST_F(GuitarChordTest, ChordZurashi)
{
    c.addKey(1);
    c.setRealButtonState(0, true);
    c.update_vcb_state();
    fuga.updateChord();
    piyo.generateNote();
    
    auto ans = note_set{67, 59, 55, 50, 47, 43};
    
    EXPECT_EQ(ans,piyo.getNotes());
    
}
