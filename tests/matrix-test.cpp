#include "gtest/gtest.h"
#include "math/matrix.h"
#include <iostream>

#include <cstddef>

TEST(matrixTests, constructorBasecase) {
    math::Matrix<float, 4, 4> m = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.1f, 2.1f, 3.1f, 4.1f},
        {1.2f, 2.2f, 3.2f, 4.2f},
        {1000.023f, 2000.023f, 3000.023f, 4000.023f}
    };

    EXPECT_EQ(1.0f, m[0][0]);
    EXPECT_EQ(2.0f, m[0][1]);
    EXPECT_EQ(3.0f, m[0][2]);
    EXPECT_EQ(4.0f, m[0][3]);

    EXPECT_EQ(1.1f, m[1][0]);
    EXPECT_EQ(2.1f, m[1][1]);
    EXPECT_EQ(3.1f, m[1][2]);
    EXPECT_EQ(4.1f, m[1][3]);

    EXPECT_EQ(1.2f, m[2][0]);
    EXPECT_EQ(2.2f, m[2][1]);
    EXPECT_EQ(3.2f, m[2][2]);
    EXPECT_EQ(4.2f, m[2][3]);

    EXPECT_EQ(1000.023f, m[3][0]);
    EXPECT_EQ(2000.023f, m[3][1]);
    EXPECT_EQ(3000.023f, m[3][2]);
    EXPECT_EQ(4000.023f, m[3][3]);
}

TEST(matrixTests, constructorCorrectSize) {
    math::Matrix<int, 5, 3> m;

    EXPECT_EQ(5, m.size());
    for (std::size_t i = 0; i < m.size(); i++) {
        EXPECT_EQ(3, m[i].size());
    }
}

TEST(matrixTests, equalityTestWithEquals) {
    math::Matrix<float, 4, 4> m1 = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.1f, 2.1f, 3.1f, 4.1f},
        {1.2f, 2.2f, 3.2f, 4.2f},
        {1000.023f, 2000.023f, 3000.023f, 4000.023f}
    };

    math::Matrix<float, 4, 4> m2 = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.1f, 2.1f, 3.1f, 4.1f},
        {1.2f, 2.2f, 3.2f, 4.2f},
        {1000.023f, 2000.023f, 3000.023f, 4000.023f}
    };

    EXPECT_EQ(m1, m2);
}

TEST(matrixTests, equalityTestWithNotEquals) {
    math::Matrix<float, 4, 4> m1 = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.1f, 2.1f, 3.1f, 4.1f},
        {1.2f, 2.2f, 3.2f, 4.2f},
        {1000.023f, 2000.025f, 3000.023f, 4000.023f}
    };

    math::Matrix<float, 4, 4> m2 = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {1.1f, 2.1f, 3.1f, 4.1f},
        {1.2f, 2.2f, 3.2f, 4.2f},
        {1000.023f, 2000.023f, 3000.023f, 4000.023f}
    };

    EXPECT_NE(m1, m2);
}