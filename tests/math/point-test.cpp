#include "gtest/gtest.h"
#include "math/point.h"

#include <cstddef>

TEST(pointTests, constructorPositiveValues) {
    math::Point<float, 5> t = {2,3,4,5,6};
    for (std::size_t i = 2, j = 0; i <= 6 && j < 5; i++, j++) {
        EXPECT_EQ(i, t[j]);
    }
}

TEST(pointTests, constructorNegativeValues) {
    math::Point<float, 5> t = {-2,-3,-4,-5,-6};
    for (int i = 2, j = 0; i <= 6 && j < 5; i++, j++) {
        EXPECT_EQ(-i, t[j]);
    }
}

TEST(pointTests, constructorSizeTest) {
    math::Point<float, 10> t;
    EXPECT_EQ(10, t.size());
}

TEST(pointTests, constructorTypesTest) {
    EXPECT_EQ(typeid(float), typeid(math::Point<float, 1>::value_type));
    EXPECT_EQ(typeid(int), typeid(math::Point<int, 1>::value_type));
    EXPECT_EQ(typeid(std::size_t), typeid(math::Point<std::size_t, 1>::value_type));
    EXPECT_EQ(typeid(unsigned), typeid(math::Point<unsigned, 1>::value_type));
    EXPECT_EQ(typeid(long), typeid(math::Point<long, 1>::value_type));
}