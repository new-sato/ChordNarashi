#include <gtest/gtest.h>
#include "GuitarChord.hpp"

class GuitarChordTest: public testing::Test
{
    protected:
    ChordButtonManager hoge;
    Button2Chord fuga=Button2Chord(hoge);
    GuitarChord piyo = GuitarChord(fuga);
    virtual void SetUp(){
    }
};

TEST_F(GuitarChordTest, C)
{   
    hoge.setRealButtonState(0, true);
    hoge.update_vcb_state();
    fuga.updateChord();
    piyo.generateNote();

    auto ans = note_set{64, 60, 55, 52,48};
    
    EXPECT_EQ(ans,piyo.getNotes());
}

TEST_F(GuitarChordTest, ChordZurashi)
{
    hoge.addKey(1);
    hoge.setRealButtonState(0, true);
    hoge.update_vcb_state();
    fuga.updateChord();
    piyo.generateNote();
    
    auto ans = note_set{67, 59, 55, 50, 47, 43};
    
    EXPECT_EQ(ans,piyo.getNotes());
    
}
