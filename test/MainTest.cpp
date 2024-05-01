#include <gtest/gtest.h>
#include <Engine.hpp>

TEST(EngineTest, BasicAssertion){
    EXPECT_STRNE("Hello","World");
    EXPECT_EQ(7*6,42);
}

TEST(EngineTest, CanBuildBarCorrectly){
    Bar bar1 = Bar(1,1,1,1,1);
    EXPECT_EQ(bar1.time,1);
    EXPECT_EQ(bar1.open,1);
    EXPECT_EQ(bar1.high,1);
    EXPECT_EQ(bar1.low,1);
    EXPECT_EQ(bar1.close,1);
}

TEST(EngineTest, CanBuildMt5BarCorrectly){
    Mt5Bar bar1 = Mt5Bar(1,1,1,1,1,1,1,1);
    EXPECT_EQ(bar1.time,1);
    EXPECT_EQ(bar1.open,1);
    EXPECT_EQ(bar1.high,1);
    EXPECT_EQ(bar1.low,1);
    EXPECT_EQ(bar1.close,1);
    EXPECT_EQ(bar1.tickvol,1);
    EXPECT_EQ(bar1.vol,1);
    EXPECT_EQ(bar1.spread,1);
}

TEST(EngineTest, CanPushBarsOnPriceSeries){
    auto priceSeries = PriceSeries<Bar>();
    Bar bar1 = Bar(1,1,1,1,1);
    Bar bar2 = Bar(2,2,2,2,2);
    EXPECT_EQ(priceSeries.size(),0);
    priceSeries.push(bar1);
    priceSeries.push(bar2);
    EXPECT_EQ(priceSeries.size(),2);
}

TEST(EngineTest, CanPushForexBarsOnPriceSeries){
    auto priceSeries = PriceSeries<Mt5Bar>();
    Mt5Bar forexbar1 = Mt5Bar(1,1,1,1,1,1,1,1);
    Mt5Bar forexbar2 = Mt5Bar(2,2,2,2,2,2,2,2);
    EXPECT_EQ(priceSeries.size(),0);
    priceSeries.push(forexbar1);
    priceSeries.push(forexbar2);
    EXPECT_EQ(priceSeries.size(),2);
}

TEST(EngineTest, CanRetriveBarsFromPriceSeries){
    auto priceSeries = PriceSeries<Bar>();
    Bar bar1 = Bar(1,1,1,1,1);
    Bar bar2 = Bar(2,2,2,2,2);
    priceSeries.push(bar1);
    priceSeries.push(bar2);
    Bar bar3 = priceSeries.at(0);
    Bar bar4 = priceSeries.at(1);
    EXPECT_TRUE(bar1==bar3);
    EXPECT_TRUE(bar2==bar4);
}

TEST(EngineTest, CanRetriveMt5BarsFromPriceSeries){
    auto priceSeries = PriceSeries<Mt5Bar>();
    Mt5Bar bar1 = Mt5Bar(1,1,1,1,1,1,1,1);
    Mt5Bar bar2 = Mt5Bar(2,2,2,2,2,2,2,2);
    priceSeries.push(bar1);
    priceSeries.push(bar2);
    Mt5Bar bar3 = priceSeries.at(0);
    Mt5Bar bar4 = priceSeries.at(1);
    EXPECT_TRUE(bar1==bar3);
    EXPECT_TRUE(bar2==bar4);
}