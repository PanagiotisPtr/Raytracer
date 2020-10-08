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

TEST(matrixTests, matrixIdentityBaseCase) {
    math::Matrix<float, 10, 10> m = math::Matrix<float, 10, 10>::getIdentity();

    for (std::size_t i = 0; i < 10; i++) {
        for (std::size_t j = 0; j < 10; j++) {
            if (i == j) {
                EXPECT_EQ(1.0, m[i][j]);
            } else {
                EXPECT_EQ(0.0, m[i][j]);
            }
        }
    }
}

TEST(matrixTests, matrixSubmatrixBasecase) {
    math::Matrix<double, 10, 10> m = {
        {10.52311, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0},
        {11.0, 21.4123, 31.0, 41.0, 51.0, 61.0, 71.0, 81.0, 91.0, 101.0},
        {12.0, 22.0, 32.3241, 42.0, 52.0, 62.0, 72.0, 82.0, 92.0, 102.0},
        {13.0, 23.0, 33.0, 43.41235, 53.0, 63.0, 73.0, 83.0, 93.0, 103.0},
        {14.0, 24.0, 34.0, 44.0, 54.5432, 64.0, 74.0, 84.0, 94.0, 104.0},
        {15.0, 25.0, 35.0, 45.0, 55.0, 65.6235, 75.0, 85.0, 95.0, 105.0},
        {16.0, 26.0, 36.0, 46.0, 56.0, 66.0, 76.6432, 86.0, 96.0, 106.0},
        {17.0, 27.0, 37.0, 47.0, 57.0, 67.0, 77.0, 87.6423, 97.0, 107.0},
        {18.0, 28.0, 38.0, 48.0, 58.0, 68.0, 78.0, 88.0, 98.623, 108.0},
        {19.0, 29.0, 39.0, 49.0, 59.0, 69.0, 79.0, 89.0, 99.0, 109.6243}
    };

    math::Matrix<double, 9, 9> m1 = m.submatrix(5, 3);

    math::Matrix<double, 9, 9> expected = {
        {10.52311, 20.0, 30.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0},
        {11.0, 21.4123, 31.0, 51.0, 61.0, 71.0, 81.0, 91.0, 101.0},
        {12.0, 22.0, 32.3241, 52.0, 62.0, 72.0, 82.0, 92.0, 102.0},
        {13.0, 23.0, 33.0, 53.0, 63.0, 73.0, 83.0, 93.0, 103.0},
        {14.0, 24.0, 34.0, 54.5432, 64.0, 74.0, 84.0, 94.0, 104.0},
        {16.0, 26.0, 36.0, 56.0, 66.0, 76.6432, 86.0, 96.0, 106.0},
        {17.0, 27.0, 37.0, 57.0, 67.0, 77.0, 87.6423, 97.0, 107.0},
        {18.0, 28.0, 38.0, 58.0, 68.0, 78.0, 88.0, 98.623, 108.0},
        {19.0, 29.0, 39.0, 59.0, 69.0, 79.0, 89.0, 99.0, 109.6243}
    };

    EXPECT_EQ(expected, m1);
}