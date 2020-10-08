#include "gtest/gtest.h"
#include "math/operations.h"
#include "math/operators.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/point.h"
#include "math/exceptions.h"

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

TEST(operationTests, vectorToMatrixBaseCaseTest) {
    math::Vector<float, 5> a = {1, 2, 3, 4, 5};
    math::Matrix<float, 1, 5> m = math::Operations::vectorToMatrix(a);

    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
    EXPECT_EQ(3, a[2]);
    EXPECT_EQ(4, a[3]);
    EXPECT_EQ(5, a[4]);
}

TEST(operationTests, matrixMultiplicationBasecase) {
    math::Matrix<double, 3, 4> a = {
        {1.123, 4.32, 33.0, 9.0},
        {-43.0, -33.0, 14.0, 6.0},
        {0.0, 0.421, -431.2, 10.0}
    };

    math::Matrix<double, 4, 3> b = {
        {10.0, 1.0, 43.0},
        {-34.0, 0.02, 2.11},
        {1.0, 2.0, 3.0},
        {4.0, 432.0, 9.99}
    };

    math::Matrix<double, 3, 3> c = {
        {-66.65, 3955.2094, 246.3142},
        {730.0, 2576.34, -1816.69},
        {-405.514, 3457.60842, -1192.81169}
    };

    EXPECT_EQ(c, a * b);
}

TEST(operationTests, matrixTransposeBasecase) {
    math::Matrix<int, 3, 5> a = {
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15}
    };

    math::Matrix<int, 5, 3> b = {
        {1, 6, 11},
        {2, 7, 12},
        {3, 8, 13},
        {4, 9, 14},
        {5, 10, 15}
    };

    EXPECT_EQ(b, math::Operations::transpose(a));
}

TEST(operationTests, matrixDeterminant1by1) {
    math::Matrix<double, 1, 1> m = {{12}};

    EXPECT_EQ(12, math::Operations::determinant(m));
}

TEST(operationTests, matrixDeterminant2by2) {
    math::Matrix<double, 2, 2> m = {
        {10.0, -43.32},
        {0.432, 33.33}
    };

    double diff = std::abs(352.01424 - math::Operations::determinant(m));

    EXPECT_LE(diff, math::EQUALITY_DELTA);
}

TEST(operationTests, matrixDeterminant10by10) {
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

    double diff = std::abs(-45.933 - math::Operations::determinant(m));

    EXPECT_LE(diff, math::EQUALITY_DELTA);
}

TEST(operationTests, matrixInverse2by2) {
    math::Matrix<double, 2, 2> m = {
        {10.0, -43.32},
        {0.432, 33.33}
    };

    math::Matrix<double, 2, 2> expected = {
        {0.094683669615183749385, 0.1230632033522280235},
        {-0.0012272230805208334753, 0.028407941678722997115}
    };

    math::Matrix<double, 2, 2> inverse = math::Operations::inverse(m);

    EXPECT_EQ(expected, inverse);
}

TEST(operationTests, matrixInverse10by10) {
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

    math::Matrix<double, 10, 10> expected = {
        {1.3252539191905333365, -0.6177327828583392158, -0.62522687569499047662, -0.36517723888201665101, -0.18138004140878630492, -0.074531583854861073501, 0.008682763411444291204, 0.089739918084988041954, 0.1760756747122546884, 0.25909072770379867933},
        {-0.61915781368505003869, 1.76064667222346495, -0.69201823563018906733, -0.42313773079476937599, -0.22952609797257368732, -0.1200903120195363333, -0.03898327529486905521, 0.038499492767961001688, 0.1196316068689927464, 0.19915546684911674748},
        {-0.62885254807914888781, -0.69431829078526680978, 2.3339222272266355004, -0.48716910639245632382, -0.2912234092157792639, -0.185246079793252969, -0.1131985472888295321, -0.046890363508106933249, 0.020182896715346659343, 0.08852405860736675289},
        {-0.36945181298061883818, -0.42675333829209299164, -0.48946888265155309563, 2.0823976516141462924, -0.22829490398830116961, -0.1711247078363810924, -0.13896566981579917916, -0.11220486114753300246, -0.087890282190367373855, -0.059974546362545707764},
        {-0.18570655252699595462, -0.23364307814061876969, -0.29471498778882253556, -0.22966706430783957818, 1.6680977533278388905, -0.14927888823945176863, -0.14344134521498514263, -0.14237515128017861136, -0.14547936772430011274, -0.14387270946214839099},
        {-0.079243213444699644124, -0.12487265605007808902, -0.18980893179215539318, -0.17351558990718546921, -0.15018636267050495598, 1.4569152992670270143, -0.15803076743065767905, -0.17387119463769173519, -0.19536042860381984227, -0.21102294685979517139},
        {0.003201977871771999547, -0.044778112637536162943, -0.11909601458011406624, -0.14244215062537596732, -0.14520070562469180867, -0.15879715441907200571, 1.3694853416274094876, -0.21685198622171728907, -0.25589250920572685174, -0.28761498593645145434},
        {0.083336708573902734946, 0.031535944185422963747, -0.054272527142223032898, -0.11684666395353184272, -0.14501788975641242278, -0.17540611635946687379, -0.21759594120735692553, 1.2913752059489080768, -0.32285987328003324544, -0.37118964742576499596},
        {0.16853101712184863809, 0.11125578804022086352, 0.01104986871754360548, -0.093872284482287617824, -0.14911217868906200144, -0.19773413700324885903, -0.25742651333823512509, -0.32362795008061656212, 1.2036023574728616433, -0.46843701786326186693},
        {0.25062066220856267872, 0.1896030353160628336, 0.077891046941389045353, -0.06713800129357178432, -0.14840426726898534933, -0.21418130092641758284, -0.28991120067588600294, -0.37272260224480521104, -0.46922724007856646645, 1.048762752336928692}
    };

    math::Matrix<double, 10, 10> inverse = math::Operations::inverse(m);

    EXPECT_EQ(expected, inverse);
}

TEST(operationTests, matrixUndoMultiplication) {
    math::Matrix<double, 3, 3> a = {
        {1.43, 1.22, 1.75},
        {2.43, 43.22, 14.75},
        {3.43, 22.22, 23.75}
    };

    math::Matrix<double, 3, 3> b = {
        {6.43, 65.3, 4.36},
        {8.43, 9.65, 6.4},
        {9.43, 2.654, 3.98}
    };

    math::Matrix<double, 3, 3> c = a * b;
    math::Matrix<double, 3, 3> bInverse = math::Operations::inverse(b);

    EXPECT_EQ(a, c * bInverse);
}

TEST(operationTests, matrixInverseFailTest) {
    math::Matrix<double, 3, 3> a = {
        {1.0,2.0,3.0},
        {1.0,2.0,3.0},
        {1.0,2.0,3.0}
    };

    EXPECT_EQ(0, math::Operations::determinant(a));

    EXPECT_THROW(math::Operations::inverse(a), math::MatrixNotInvertableException);
}