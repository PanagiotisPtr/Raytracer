#include "gtest/gtest.h"
#include "math/tensor.h"

TEST(tensorTests, dimensionalityTest1) {
    math::Tensor<float, 5> t(2,3,4,5,6);
    EXPECT_EQ (true, true);
}