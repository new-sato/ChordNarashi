#include <gtest/gtest.h>
#include "ChordButtonManager.hpp"
#include "oncebutton.hpp"
#include "winButtonUpdater.hpp"

class WinButtonTest: public testing::Test
{
    protected:
    std::vector<Button> ChordButtons = std::vector<Button>(60);
    std::vector<Button> ShiftButtons = std::vector<Button>(12);
    std::vector<OnceButton> KeyButtons = std::vector<OnceButton>(4);
    std::vector<Button> rightButtons = std::vector<Button>(1);
    std::vector<OnceButton> otherButton = std::vector<OnceButton>(1);
    winButtonUpdater wbu = winButtonUpdater(ChordButtons, ShiftButtons, KeyButtons, rightButtons, otherButton);
    virtual void SetUp(){}
};

TEST_F(WinButtonTest, S)
{
    wbu.updateAllButtons();
    EXPECT_EQ(1,1);
    EXPECT_EQ(ChordButtons[0].getIsPressed(),false);
}
