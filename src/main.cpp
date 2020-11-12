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

    objects::Sphere floor({0,0,0,1});
    floor.setMaterial(primitives::BaseMaterial(
        drawing::Colour({0.2, 0.2, 0.2}),
        1,
        0.9,
        0.9,
        200.0
    ));

    floor.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(10.0, 0.01, 10.0)
    );

    floor.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.0,-0.6,0.0)
    );

    world::World w;
    w.addObject(s);
    w.addObject(l);
    w.addObject(floor);

    world::Camera<1280, 720> camera(M_PI/3);
    camera.setTransformation(world::Operations::calculateCameraTransformation(
        primitives::Point3D({0,0,-4,1}),
        primitives::Point3D({0,0,0,1}),
        primitives::Vector3D({0,1,0,1})
    ));
    auto image = camera.render(w);
    image->save("render.ppm");

    delete image;

    return 0;
}