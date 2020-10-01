#include "gtest/gtest.h"
#include "math/operations.h"
#include "math/operators.h"
#include "math/vector.h"

#include <cstddef>
#include <cmath>

TEST(operationTests, additionBaseCase) {
    math::Vector<float, 5> a = {1, 2, 3, 4, 5};
    math::Vector<float, 5> b = {5, 4, 3, 2, 1};
    math::Vector<float, 5> c = a + b;
    math::Vector<float, 5> d = math::Operations::add(a, b);

    EXPECT_EQ(c, d);
    EXPECT_EQ(6, c[0]);
    EXPECT_EQ(6, c[1]);
    EXPECT_EQ(6, c[2]);
    EXPECT_EQ(6, c[3]);
    EXPECT_EQ(6, c[4]);
}

TEST(operationTests, additionNegativeNumbersBaseCase) {
    math::Vector<int, 5> a = {-1, 2, -3, 4, -5};
    math::Vector<int, 5> b = {5, -4, 3, -2, 1};
    math::Vector<int, 5> c = a + b;
    math::Vector<int, 5> d = math::Operations::add(a, b);

    EXPECT_EQ(c, d);
    EXPECT_EQ(4, c[0]);
    EXPECT_EQ(-2, c[1]);
    EXPECT_EQ(0, c[2]);
    EXPECT_EQ(2, c[3]);
    EXPECT_EQ(-4, c[4]);
}

TEST(operationTests, subtractionVectorBaseCase) {
    math::Vector<float, 5> a = {1, 2, 3, 4, 5};
    math::Vector<float, 5> b = {5, 4, 3, 2, 1};
    math::Vector<float, 5> c = a - b;
    math::Vector<float, 5> d = math::Operations::subtract(a, b);

    EXPECT_EQ(c, d);
    EXPECT_EQ(-4, c[0]);
    EXPECT_EQ(-2, c[1]);
    EXPECT_EQ(0, c[2]);
    EXPECT_EQ(2, c[3]);
    EXPECT_EQ(4, c[4]);
}

TEST(operationTests, subtractionVectorNegativeNumbersBaseCase) {
    math::Vector<int, 5> a = {-1, 2, -3, 4, -5};
    math::Vector<int, 5> b = {5, -4, 3, -2, 1};
    math::Vector<int, 5> c = a - b;
    math::Vector<int, 5> d = math::Operations::subtract(a, b);

    EXPECT_EQ(c, d);
    EXPECT_EQ(-6, c[0]);
    EXPECT_EQ(6, c[1]);
    EXPECT_EQ(-6, c[2]);
    EXPECT_EQ(6, c[3]);
    EXPECT_EQ(-6, c[4]);
}

TEST(operationTests, subtractionPointTests) {
    math::Point<float, 5> a = {1, 2, 3, 4, 5};
    math::Point<float, 5> b = {5, 4, 3, 2, 1};
    math::Vector<float, 5> c = a - b;

    EXPECT_EQ(-4, c[0]);
    EXPECT_EQ(-2, c[1]);
    EXPECT_EQ(0, c[2]);
    EXPECT_EQ(2, c[3]);
    EXPECT_EQ(4, c[4]);
}

TEST(operationTests, subtractionPointVectorTests) {
    math::Point<float, 5> a = {1, 2, 3, 4, 5};
    math::Vector<float, 5> b = {5, 4, 3, 2, 1};
    math::Point<float, 5> c = a - b;

    EXPECT_EQ(-4, c[0]);
    EXPECT_EQ(-2, c[1]);
    EXPECT_EQ(0, c[2]);
    EXPECT_EQ(2, c[3]);
    EXPECT_EQ(4, c[4]);
}

TEST(operationTests, scalarMultiplicationTest) {
    math::Vector3D<float> a = {1.0f, -2.0f, 0.5f};
    float c = 43.242;
    math::Vector3D<float> ac = a * c;

    EXPECT_EQ(a[0] * c, ac[0]);
    EXPECT_EQ(a[1] * c, ac[1]);
    EXPECT_EQ(a[2] * c, ac[2]);
}

TEST(operationTests, scalarDivisionTest) {
    math::Vector3D<float> a = {1.0f, -2.0f, 0.5f};
    float c = 43.242;
    math::Vector3D<float> ac = a / c;

    EXPECT_EQ(a[0] / c, ac[0]);
    EXPECT_EQ(a[1] / c, ac[1]);
    EXPECT_EQ(a[2] / c, ac[2]);
}

TEST(operationTests, magnitudeUnitTestOnX) {
    math::Vector3D<float> a = {1.0f, 0.0f, 0.0f};
    float m = math::Operations::magnitude(a);

    EXPECT_EQ(1, m);
}

TEST(operationTests, magnitudeUnitTestOnY) {
    math::Vector3D<float> a = {0.0f, 1.0f, 0.0f};
    float m = math::Operations::magnitude(a);

    EXPECT_EQ(1, m);
}

TEST(operationTests, magnitudeUnitTestOnZ) {
    math::Vector3D<float> a = {0.0f, 0.0f, 1.0f};
    float m = math::Operations::magnitude(a);

    EXPECT_EQ(1, m);
}

TEST(operationTests, magnitudeBaseCaseTest) {
    math::Vector<float, 5> a = {1.0f, -3.43f, 44.44f, 92.0f, 0.0f};
    float m = math::Operations::magnitude(a);
    float expected = (1.0f*1.0f) + ((-3.43f)*(-3.43f)) + (44.44f*44.44f) + (92.0f*92.0f) + (0.0f*0.0f);
    expected = sqrt(expected);

    EXPECT_EQ(expected, m);
}

TEST(operationTests, normalisationBaseCaseTest) {
    math::Vector<float, 5> a = {1.0f, -3.43f, 44.44f, 92.0f, 0.0f};
    math::Vector<float, 5> norm = math::Operations::normalise(a);
    float expectedM = (1.0f*1.0f) + ((-3.43f)*(-3.43f)) + (44.44f*44.44f) + (92.0f*92.0f) + (0.0f*0.0f);
    expectedM = sqrt(expectedM);
    math::Vector<float, 5> expectedV = {
        a[0]/expectedM,
        a[1]/expectedM,
        a[2]/expectedM,
        a[3]/expectedM,
        a[4]/expectedM
    };

    // this is important. It does comparison of double as well
    // (e.g difference of 0.0001 is cosnidered equal)
    EXPECT_EQ(expectedV, norm);
}

TEST(operationTests, dotProductBaseCaseTest) {
    math::Vector<float, 5> a = {1, 2, 3, 4, 5};
    math::Vector<float, 5> b = {5, 4, 3, 2, 1};
    float d = math::Operations::dotProduct(a, b);
    float expected = 1*5 + 2*4 + 3*3 + 4*2 + 5*1;

    EXPECT_EQ(expected, d);
}

TEST(operationTests, dotProductNegativeNumbersTest) {
    math::Vector<float, 5> a = {1, -2, 3, -4, 5};
    math::Vector<float, 5> b = {-5, 4, -3, 2, -1};
    float d = math::Operations::dotProduct(a, b);
    float expected = -(1*5 + 2*4 + 3*3 + 4*2 + 5*1);

    EXPECT_EQ(expected, d);
}

TEST(operationTests, crossProduct3DTest) {
    math::Vector<float, 3> a = {-2.5f, 4.0f, 5.32f};
    math::Vector<float, 3> b = {3.0f, -2.323f, 1.0f};
    math::Vector3D<float> d = math::Operations::crossProduct3D(a, b);
    math::Vector3D<float> expected = {
        (4.0f) * (1.0f) - (5.32f) * (-2.323f),
        (5.32f) * (3.0f) - (-2.5f) * (1.0f),
        (-2.5f) * (-2.323f) - (4.0f) * (3.0f)
    };

    EXPECT_EQ(expected, d);
}