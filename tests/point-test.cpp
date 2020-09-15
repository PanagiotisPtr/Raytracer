#include "gtest/gtest.h"
#include "math/point.h"

TEST(pointTests, constructorTest1) {
    math::Point<float, 5> t = {2,3,4,5,6};
    EXPECT_EQ (true, true);
}