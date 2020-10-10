#include <cstddef>

#include "gtest/gtest.h"
#include "math/utility.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/matrix.h"
#include "math/operations.h"

TEST(utilityTests, vectorToMatrixBaseCaseTest) {
    math::Vector<float, 5> a = {1, 2, 3, 4, 5};
    math::Matrix<float, 5, 1> m = math::Utility::vectorToMatrix(a);

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[1][0]);
    EXPECT_EQ(3, m[2][0]);
    EXPECT_EQ(4, m[3][0]);
    EXPECT_EQ(5, m[4][0]);
}

TEST(utilityTests, pointToMatrixBaseCaseTest) {
    math::Point<float, 5> p = {1, 2, 3, 4, 5};
    math::Matrix<float, 5, 1> m = math::Utility::pointToMatrix(p);

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[1][0]);
    EXPECT_EQ(3, m[2][0]);
    EXPECT_EQ(4, m[3][0]);
    EXPECT_EQ(5, m[4][0]);
}

TEST(utilityTests, matrixToPointBaseCaseTest) {
    math::Vector<float, 5> v = {1, 2, 3, 4, 5};

    ASSERT_EQ(v, math::Utility::matrixToVector(math::Utility::vectorToMatrix(v)));
}

TEST(utilityTests, matrixToVectorBaseCaseTest) {
    math::Point<float, 5> p = {1, 2, 3, 4, 5};

    ASSERT_EQ(p, math::Utility::matrixToPoint(math::Utility::pointToMatrix(p)));
}

TEST(utilityTests, matrixToPointTransposeTest) {
    math::Vector<float, 5> v = {1, 2, 3, 4, 5};

    ASSERT_EQ(v, math::Utility::matrixToVector(
        math::Operations::transpose(math::Utility::vectorToMatrix(v)))
    );
}

TEST(utilityTests, matrixToVectorTransposeTest) {
    math::Point<float, 5> p = {1, 2, 3, 4, 5};

    ASSERT_EQ(p, math::Utility::matrixToPoint(
        math::Operations::transpose(math::Utility::pointToMatrix(p)))
    );
}