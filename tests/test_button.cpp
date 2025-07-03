#include <gtest/gtest.h>
#include "button.hpp"

TEST(ButtonTest, getter)
{
    Button b;
    EXPECT_EQ(false, b.getIsPressed());
    b.setIsPressed(true);
    EXPECT_EQ(true, b.getIsPressed());
}
