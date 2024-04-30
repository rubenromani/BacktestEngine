#include <gtest/gtest.h>
#include <Engine.hpp>

TEST(HelloTest, BasicAssertion){
    EXPECT_STRNE("Hello","World");
    EXPECT_EQ(7*6,42);
}