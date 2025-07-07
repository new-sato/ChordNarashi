#include <gtest/gtest.h>
#include "ChordButtonManager.hpp"

class CBMTest: public testing::Test
{
    protected:
    ChordButtonManager c= ChordButtonManager();
    virtual void SetUp(){}
};

TEST_F(CBMTest, set)
{
    c.setRealButtonState(0,true);
    EXPECT_EQ(false,c.is_all_button_releaced());
}

TEST_F(CBMTest, check)
{
    EXPECT_EQ(true,c.is_all_button_releaced());
}

TEST_F(CBMTest, itidoosi)
{
    c.setRealButtonState(0,true);
    c.update_vcb_state();
    EXPECT_EQ(VirtualChordButton(0,0).note,(c.getVirtualChordButtons().begin())->note);
}

TEST_F(CBMTest, itidooshi_hanasi)
{
    c.setRealButtonState(0,true);
    c.update_vcb_state();
    c.setRealButtonState(0,false);
    c.update_vcb_state();

    EXPECT_EQ(1,c.getVirtualChordButtons().size());
}

TEST_F(CBMTest, nidooshi_hanasi)
{
    c.setRealButtonState(0,true);
    c.update_vcb_state();
    c.setRealButtonState(1,true);
    c.update_vcb_state();
    c.setRealButtonState(0,false);
    c.update_vcb_state();
    
    std::set<VirtualChordButton> ans1 = c.getVirtualChordButtons(); 

    EXPECT_EQ(2,ans1.size());
}

TEST_F(CBMTest, itidoItidooshi)
{
    c.setRealButtonState(0,true);
    c.update_vcb_state();
    c.setRealButtonState(0,false);
    c.update_vcb_state();
    c.setRealButtonState(1,true);
    c.update_vcb_state();

    EXPECT_EQ(VirtualChordButton(1,0).cbt,(c.getVirtualChordButtons().begin())->cbt);
    EXPECT_EQ(VirtualChordButton(1,0).note,(c.getVirtualChordButtons().begin())->note);
    EXPECT_EQ(1,c.getVirtualChordButtons().size());

}

TEST(VCBTest, chordTypeTest)
{
    auto temp = VirtualChordButton(11,0);
    EXPECT_EQ(temp.cbt, ChordButtonType::Major);
    EXPECT_EQ(temp.note, Note::F);

    auto temp1 = VirtualChordButton(12,0);
    EXPECT_EQ(temp1.cbt, ChordButtonType::minor);
    EXPECT_EQ(temp1.note, Note::A);

    auto temp2 = VirtualChordButton(24,0);
    EXPECT_EQ(temp2.cbt, ChordButtonType::dim);
    EXPECT_EQ(temp2.note, Note::B);
}
