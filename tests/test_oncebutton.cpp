#include <gtest/gtest.h>
#include "oncebutton.hpp"

class OnceButtonTest :public testing::Test{
    protected:
    OnceButton o;
    virtual void SetUp(){}
};

TEST_F(OnceButtonTest, nomal)
{
    EXPECT_EQ(false,o.getIsPressed());
    o.setIsPressed(true);
    EXPECT_EQ(true,o.getIsPressed());
}

TEST_F(OnceButtonTest, fukuzatu)
{
    o.setIsPressed(true);
    EXPECT_EQ(true,o.getIsPressed());
    EXPECT_EQ(false,o.getIsPressed());
    EXPECT_EQ(false,o.getIsPressed());
    o.setIsPressed(false);
    EXPECT_EQ(false,o.getIsPressed());
    EXPECT_EQ(false,o.getIsPressed());
    o.setIsPressed(true);
    EXPECT_EQ(true,o.getIsPressed());
}
