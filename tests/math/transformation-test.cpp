#include "gtest/gtest.h"
#include "math/transformations.h"
#include "math/utility.h"
#include "math/operators.h"
#include "math/point.h"

#include <cstddef>
#include <math.h>

TEST(transformationTest, translationTest) {
    math::Point<double, 4> p = {5.0, 2.0, 10.0, 1.0};
    math::Matrix<double, 4, 4> m = math::Transformations::translate(1.0, 3.3, 1.1);

    auto result = m * math::Utility::pointToMatrix(p);

    EXPECT_EQ(6.0, result[0][0]);
    EXPECT_EQ(5.3, result[1][0]);
    EXPECT_EQ(11.1, result[2][0]);
}

TEST(transformationTest, scaleTest) {
    math::Point<double, 4> p = {5.0, 2.0, 10.0, 1.0};
    math::Matrix<double, 4, 4> m = math::Transformations::scale(1.43, -3.3, 1.0);

    auto result = m * math::Utility::pointToMatrix(p);

    EXPECT_EQ(5.0 * 1.43, result[0][0]);
    EXPECT_EQ(2.0 * (-3.3), result[1][0]);
    EXPECT_EQ(10.0, result[2][0]);
}

TEST(transformationTest, rotationXTest) {
    math::Point<double, 4> p = {5.0, 2.0, 10.0, 1.0};
    math::Matrix<double, 4, 4> m = math::Transformations::rotateX(M_PI/2.0);

    auto result = m * math::Utility::pointToMatrix(p);

    EXPECT_DOUBLE_EQ(5.0, result[0][0]);
    EXPECT_DOUBLE_EQ(-10.0, result[1][0]);
    EXPECT_DOUBLE_EQ(2.0, result[2][0]);
    EXPECT_DOUBLE_EQ(1.0, result[3][0]);
}

TEST(transformationTest, rotationYTest) {
    math::Point<double, 4> p = {5.0, 2.0, 10.0, 1.0};
    math::Matrix<double, 4, 4> m = math::Transformations::rotateY(M_PI/2.0);

    auto result = m * math::Utility::pointToMatrix(p);

    EXPECT_DOUBLE_EQ(10.0, result[0][0]);
    EXPECT_DOUBLE_EQ(2.0, result[1][0]);
    EXPECT_DOUBLE_EQ(-5.0, result[2][0]);
    EXPECT_DOUBLE_EQ(1.0, result[3][0]);
}

TEST(transformationTest, rotationZTest) {
    math::Point<double, 4> p = {5.0, 2.0, 10.0, 1.0};
    math::Matrix<double, 4, 4> m = math::Transformations::rotateZ(M_PI/2.0);

    auto result = m * math::Utility::pointToMatrix(p);

    EXPECT_DOUBLE_EQ(-2.0, result[0][0]);
    EXPECT_DOUBLE_EQ(5.0, result[1][0]);
    EXPECT_DOUBLE_EQ(10.0, result[2][0]);
}