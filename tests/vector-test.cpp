#include "gtest/gtest.h"
#include "math/vector.h"

#include <cstddef>

TEST(vectorTests, constructorPositiveValues) {
    math::Vector<float, 5> t = {2,3,4,5,6};
    for (std::size_t i = 2, j = 0; i <= 6 && j < 5; i++, j++) {
        EXPECT_EQ(i, t[j]);
    }
}

TEST(vectorTests, constructorNegativeValues) {
    math::Vector<float, 5> t = {-2,-3,-4,-5,-6};
    for (int i = 2, j = 0; i <= 6 && j < 5; i++, j++) {
        EXPECT_EQ(-i, t[j]);
    }
}

TEST(vectorTests, constructorSizeTest) {
    math::Vector<float, 10> t;
    EXPECT_EQ(10, t.size());
}

TEST(vectorTests, constructorTypesTest) {
    EXPECT_EQ(typeid(float), typeid(math::Vector<float, 1>::value_type));
    EXPECT_EQ(typeid(int), typeid(math::Vector<int, 1>::value_type));
    EXPECT_EQ(typeid(std::size_t), typeid(math::Vector<std::size_t, 1>::value_type));
    EXPECT_EQ(typeid(unsigned), typeid(math::Vector<unsigned, 1>::value_type));
    EXPECT_EQ(typeid(long), typeid(math::Vector<long, 1>::value_type));
}