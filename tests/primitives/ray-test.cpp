#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>

#include "primitives/ray.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/operators.h"

TEST(rayTests, constructorBaseCase) {
    math::Point<primitives::PrecisionType, 4> origin = {0,0,0,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,0,0};

    primitives::Ray r(origin, direction);

    ASSERT_EQ(origin, r.getOrigin());
    ASSERT_EQ(direction, r.getDirection());
}

TEST(rayTests, getPositionAtTimeBaseCase) {
    primitives::Point3D origin = {0,0,0,1};
    primitives::Vector3D direction = {1,1,1,0};

    primitives::Ray r(origin, direction);

    primitives::PrecisionType t = 1.53;
    primitives::Point3D target = origin + direction * t;

    ASSERT_EQ(target, r.getAtTime(t));
}