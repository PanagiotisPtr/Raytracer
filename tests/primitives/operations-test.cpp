#include <cstddef>
#include "gtest/gtest.h"
#include "primitives/constants.h"
#include "primitives/ray.h"
#include "primitives/intersection.h"
#include "primitives/intersection_container.h"
#include "primitives/operations.h"
#include "objects/sphere.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/operators.h"
#include "math/transformations.h"
#include "math/utility.h"

TEST(rayTransformationOperationsTests, rayTransformationTranslate) {
    primitives::Ray r1({1,2,3,1}, {0,1,2,0});

    primitives::TransformationMatrix m =
        math::Transformations::translate<primitives::PrecisionType>(4,5,6);

    primitives::Ray r2 = primitives::Operations::transformRay(r1, m);

    primitives::Point3D expectedOrigin = {5, 7, 9, 1};
    primitives::Vector3D expectedDirection = {0,1,2,0};

    ASSERT_EQ(expectedOrigin, r2.getOrigin());
    ASSERT_EQ(expectedDirection, r2.getDirection());
}

TEST(rayTransformationOperationsTests, rayTransformationScale) {
    primitives::Ray r1({1,2,3,1}, {0,1,2,0});

    primitives::TransformationMatrix m =
        math::Transformations::scale<primitives::PrecisionType>(4,5,6);

    primitives::Ray r2 = primitives::Operations::transformRay(r1, m);

    primitives::Point3D expectedOrigin = {4, 10, 18, 1};
    primitives::Vector3D expectedDirection = {0,5,12,0};

    ASSERT_EQ(expectedOrigin, r2.getOrigin());
    ASSERT_EQ(expectedDirection, r2.getDirection());
}

TEST(intersectionOperationsTests, raySphereBaseCase) {
    math::Point<primitives::PrecisionType, 4> origin = {0,0,-2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(2, c.front.size());
    EXPECT_EQ(0, c.back.size());

    primitives::Intersection first = *std::begin(c.front);
    primitives::Intersection second = *std::next(std::begin(c.front));

    EXPECT_EQ(&s, first.target);
    EXPECT_EQ(&s, second.target);

    EXPECT_EQ(first.time, c.getFirst().time);
    EXPECT_EQ(first.target, c.getFirst().target);

    EXPECT_DOUBLE_EQ(1, first.time);
    EXPECT_DOUBLE_EQ(3, second.time);
}

TEST(intersectionOperationsTests, raySphereBorderLineIntersection) {
    math::Point<primitives::PrecisionType, 4> origin = {0,1,-2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(1, c.front.size());
    EXPECT_EQ(0, c.back.size());

    primitives::Intersection first = *std::begin(c.front);

    EXPECT_EQ(&s, first.target);

    EXPECT_EQ(first.time, c.getFirst().time);

    EXPECT_DOUBLE_EQ(2, first.time);
}

TEST(intersectionOperationsTests, raySphereNoIntersection) {
    math::Point<primitives::PrecisionType, 4> origin = {0.0,1.1,-2.0,1.0};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(0, c.front.size());
    EXPECT_EQ(0, c.back.size());
}

TEST(intersectionOperationsTests, raySphereOneBehindOneInFront) {
    math::Point<primitives::PrecisionType, 4> origin = {0,0,0,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(1, c.front.size());
    EXPECT_EQ(1, c.back.size());

    primitives::Intersection first = *std::begin(c.front);
    primitives::Intersection second = *std::begin(c.back);

    EXPECT_EQ(&s, first.target);
    EXPECT_EQ(&s, second.target);

    EXPECT_EQ(first.time, c.getFirst().time);
    EXPECT_EQ(first.target, c.getFirst().target);

    EXPECT_DOUBLE_EQ(1, first.time);
    EXPECT_DOUBLE_EQ(-1, second.time);
}

TEST(intersectionOperationsTests, raySphereBothBehind) {
    math::Point<primitives::PrecisionType, 4> origin = {0,0,2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(0, c.front.size());
    EXPECT_EQ(2, c.back.size());

    primitives::Intersection first = *std::begin(c.back);
    primitives::Intersection second = *std::next(std::begin(c.back));

    EXPECT_EQ(&s, first.target);
    EXPECT_EQ(&s, second.target);

    EXPECT_DOUBLE_EQ(-1, first.time);
    EXPECT_DOUBLE_EQ(-3, second.time);
}

TEST(intersectionOperationsTests, raySphereScaledSphere) {
    math::Point<primitives::PrecisionType, 4> origin = {0,2,-2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    s.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(2,2,2)
    );

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(1, c.front.size());
    EXPECT_EQ(0, c.back.size());

    primitives::Intersection first = *std::begin(c.front);

    EXPECT_EQ(&s, first.target);

    EXPECT_EQ(first.time, c.getFirst().time);
    EXPECT_EQ(first.target, c.getFirst().target);

    EXPECT_DOUBLE_EQ(2, first.time);
}

TEST(intersectionOperationsTests, raySphereMovedSphere) {
    math::Point<primitives::PrecisionType, 4> origin = {0,2,-2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    s.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(2,2,2)
    );

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(1, c.front.size());
    EXPECT_EQ(0, c.back.size());

    primitives::Intersection first = *std::begin(c.front);

    EXPECT_EQ(&s, first.target);

    EXPECT_EQ(first.time, c.getFirst().time);
    EXPECT_EQ(first.target, c.getFirst().target);

    EXPECT_DOUBLE_EQ(2, first.time);
}

TEST(intersectionOperationsTests, raySphereMovedAndScaledSphere) {
    math::Point<primitives::PrecisionType, 4> origin = {0,2,-2,1};
    math::Vector<primitives::PrecisionType, 4> direction = {0,0,1,0};
    primitives::Point3D p = {0,0,0,1};

    primitives::Ray r(origin, direction);
    objects::Sphere s(p);

    s.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(2,2,2)
    );

    s.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0,2,0)
    );

    primitives::IntersectionContainer c = primitives::Operations::getRsaySphereIntersections(r, &s);

    EXPECT_EQ(2, c.front.size());
    EXPECT_EQ(0, c.back.size());

    primitives::Intersection first = *std::begin(c.front);
    primitives::Intersection second = *std::next(std::begin(c.front));

    EXPECT_EQ(&s, first.target);
    EXPECT_EQ(&s, second.target);

    EXPECT_EQ(first.time, c.getFirst().time);
    EXPECT_EQ(first.target, c.getFirst().target);

    EXPECT_DOUBLE_EQ(0, first.time);
    EXPECT_DOUBLE_EQ(4, second.time);
}