#include <gtest/gtest.h>
#include "ChordButtonManager.hpp"

class CBMTest: public testing::Test
{
    protected:
    ChordButtonManager c;
    virtual void SetUp(){}
};

TEST_F(CBMTest, set)
{
    c.setButtonState(0,true);
    EXPECT_EQ(false,c.is_all_button_releaced());
}

TEST_F(CBMTest, check)
{
    EXPECT_EQ(true,c.is_all_button_releaced());
}

TEST_F(CBMTest, itidoosi)
{
    c.setButtonState(0,true);
    c.update_vcb_state();
    EXPECT_EQ(true,c.getVirtualChordButtons()[0]);
}

TEST_F(CBMTest, itidooshi_hanasi)
{
    c.setButtonState(0,true);
    c.update_vcb_state();
    c.setButtonState(0,false);
    c.update_vcb_state();

    EXPECT_EQ(true,c.getVirtualChordButtons()[0]);
}

TEST_F(CBMTest, nidooshi_hanasi)
{
    c.setButtonState(0,true);
    c.update_vcb_state();
    c.setButtonState(1,true);
    c.update_vcb_state();
    c.setButtonState(0,false);
    c.update_vcb_state();
    
    std::vector<bool> ans1 = c.getVirtualChordButtons(); 

    EXPECT_EQ(true,ans1[0]);
    EXPECT_EQ(true,ans1[1]);
}

TEST_F(CBMTest, itidoItidooshi)
{
    c.setButtonState(0,true);
    c.update_vcb_state();
    c.setButtonState(0,false);
    c.update_vcb_state();
    c.setButtonState(1,true);
    c.update_vcb_state();

    EXPECT_EQ(false,c.getVirtualChordButtons()[0]);
    EXPECT_EQ(true,c.getVirtualChordButtons()[1]);

}