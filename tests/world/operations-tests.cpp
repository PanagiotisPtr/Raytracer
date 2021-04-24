#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>
#include <iostream>

#include "world/world.h"
#include "world/operations.h"
#include "math/transformations.h"
#include "primitives/ray.h"
#include "primitives/intersection_container.h"
#include "primitives/constants.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "objects/light.h"

TEST(reflectivityColourTest, colourWithReflectivity) {
    world::World w;
    primitives::Ray r({2.0,0.0,0.0,1.0}, {-1.0,0.0,1.0,0.0});
    objects::Sphere s;
    objects::Plane p;
    objects::Light l(
        drawing::Colour({1.0,1.0,1.0}),
        primitives::Point3D({2,-2,-10,1})
    );

    p.setMaterial(primitives::BaseMaterial(
        drawing::Colour({1.0, 0.0, 0.0}),
        1,
        0.9,
        0.9,
        200.0
    ));

    s.setMaterial(primitives::BaseMaterial(
        drawing::Colour({0.0, 0.7, 0.3}),
        1,
        0.9,
        0.9,
        200.0,
        0.5
    ));

    s.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.0, 0.0, 1.0)
    );

    p.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(M_PI/2)
    );

    p.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0,0,3)
    );

    w.addObject(s);
    w.addObject(p);
    w.addObject(l);

    drawing::Colour c = world::Operations::colourAtIntersection(w, r, 2);

    ASSERT_DOUBLE_EQ(c.red(), 0);
}

TEST(refractionWorldTests, testRefractedRay) {
    world::World w;
    objects::Plane p;
    objects::Light l({1,1,1}, {0,0,0,1});

    p.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(M_PI/2)
    );

    p.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0,4,0)
    );

    p.setMaterial(primitives::BaseMaterial(
        drawing::Colour({0.3, 0.5, 0.2}),
        1,
        1.0,
        0.2,
        20.0
    ));

    objects::Sphere s1;

    s1.setMaterial(primitives::BaseMaterial(
        drawing::Colour({0.0, 0.0, 0.0}),
        1,
        1.0,
        1,
        300.0,
        1,
        1.0,
        1.52
    ));

    w.addObject(s1);    
    w.addObject(p);
    w.addObject(l);
    
    primitives::Ray r(primitives::Point3D({0.0,-0.5,-2.0,1.0}), primitives::Vector3D({0,0,1,0}));

    drawing::Colour c = world::Operations::colourAtIntersection(w, r);

    bool colourIsBlack = c.red() == 0 && c.green() == 0 && c.blue() == 0;

    EXPECT_EQ(false, colourIsBlack);
}