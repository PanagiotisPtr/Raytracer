#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>

#include "world/world.h"
#include "math/transformations.h"
#include "primitives/ray.h"
#include "primitives/intersection_container.h"
#include "primitives/constants.h"

TEST(worldTests, constructorBaseCase) {
    world::World w;

    ASSERT_EQ(0, w.getLights().size());
    ASSERT_EQ(0, w.getObjects().size());
}

TEST(worldTests, addObjectToWorld) {
    world::World w;
    objects::Sphere s({0,0,0,1});

    w.addObject(s);

    ASSERT_EQ(0, w.getLights().size());
    ASSERT_EQ(1, w.getObjects().size());

    const objects::Object& r = w.getObjects()[0];

    ASSERT_EQ(s.getOrigin(), r.getOrigin());
}

TEST(worldTests, addLightToWorld) {
    world::World w;
    objects::Light l({1,1,1}, {0,0,0,1});

    w.addObject(l);

    ASSERT_EQ(1, w.getLights().size());
    ASSERT_EQ(0, w.getObjects().size());

    objects::Light i = w.getLights()[0];

    ASSERT_EQ(l.getOrigin(), i.getOrigin());

    ASSERT_DOUBLE_EQ(l.getIntensity().red(), i.getIntensity().red());
    ASSERT_DOUBLE_EQ(l.getIntensity().green(), i.getIntensity().green());
    ASSERT_DOUBLE_EQ(l.getIntensity().blue(), i.getIntensity().blue());
}

TEST(worldTests, rayWorldIntersections) {
    world::World w;
    objects::Sphere s1({0,0,0,1});
    objects::Sphere s2({0,0,0,1});
    objects::Light l({1,1,1}, {0,2,0,1});

    s2.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.25, 0.25, 0.25)
    );

    s2.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0, 0, 2)
    );

    w.addObject(s1);
    w.addObject(s2);
    w.addObject(l);

    primitives::Ray r({0,0,-5,1}, {0,0,1,0});

    primitives::IntersectionContainer c = w.getIntersections(r);

    EXPECT_EQ(0, c.back.size());
    EXPECT_EQ(4, c.front.size());

    EXPECT_DOUBLE_EQ(4, begin(c.front)->time);
    c.front.erase(begin(c.front));

    EXPECT_DOUBLE_EQ(6, begin(c.front)->time);
    c.front.erase(begin(c.front));

    EXPECT_DOUBLE_EQ(6.75, begin(c.front)->time);
    c.front.erase(begin(c.front));

    EXPECT_DOUBLE_EQ(7.25, begin(c.front)->time);
    c.front.erase(begin(c.front));
}