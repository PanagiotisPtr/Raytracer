#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>
#include <iostream>

#include "world/world.h"
#include "world/Operations.h"
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

    ASSERT_GT(c.red(), 0);
}