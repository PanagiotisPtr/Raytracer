#include <iostream>

#include "math/point.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/operations.h"
#include "math/operators.h"
#include "math/transformations.h"

#include "drawing/colour.h"
#include "drawing/canvas.h"

#include "primitives/constants.h"
#include "primitives/ray.h"
#include "primitives/operations.h"

#include "objects/sphere.h"
#include "objects/light.h"

#include "world/world.h"
#include "world/camera.h"
#include "world/operations.h"

#define IMAGE_SIZE_X 1080
#define IMAGE_SIZE_Y 1080

int main() {
    objects::Sphere s({0,0,0,1});
    s.setMaterial(primitives::BaseMaterial(
        drawing::Colour({0.4, 1.0, 0.4}),
        1,
        0.9,
        0.9,
        200.0
    ));

    s.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.5,0.0,0.0)
    );

    s.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(1.0,0.6,1.0)
    );

    objects::Light l(
        drawing::Colour({1.0,1.0,1.0}),
        primitives::Point3D({-10,10,-10,1})
    );

    world::World w;
    w.addObject(s);
    w.addObject(l);

    world::Camera<200, 100> camera(M_PI/3);
    camera.setTransformation(world::Operations::calculateCameraTransformation(
        primitives::Point3D({0,0,-4,1}),
        primitives::Point3D({0,0,0,1}),
        primitives::Vector3D({0,1,0,1})
    ));
    (camera.render(w)).save("render.ppm");

    return 0;
}