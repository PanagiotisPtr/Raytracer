#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>

#include "primitives/intersection_container.h"
#include "primitives/exceptions.h"

TEST(intersectionContainerTests, testEmptyFrontException) {
    primitives::IntersectionContainer c;

    EXPECT_THROW(c.getFirst(), primitives::NoIntersectionsException);
}