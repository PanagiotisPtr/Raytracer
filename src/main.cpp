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
#include "world/operations.h"

#define IMAGE_SIZE_X 1080
#define IMAGE_SIZE_Y 1080

int main() {
    primitives::Point3D cameraOrigin = {0,0,-4,1};
    auto canvas = (drawing::Canvas<IMAGE_SIZE_X, IMAGE_SIZE_Y>*)
        malloc(sizeof(drawing::Canvas<IMAGE_SIZE_X, IMAGE_SIZE_Y>));
    primitives::PrecisionType aspectRatio =
        (primitives::PrecisionType)IMAGE_SIZE_X/(primitives::PrecisionType)IMAGE_SIZE_Y;
    primitives::PrecisionType canvasSizeX = 10 * aspectRatio;
    primitives::PrecisionType canvasSizeY = 10;
    primitives::PrecisionType canvasZPosition = 10.0;
    primitives::PrecisionType canvasWidth = IMAGE_SIZE_X;
    primitives::PrecisionType canvasHeight = IMAGE_SIZE_Y;
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
    
    for (std::size_t i = 0; i < IMAGE_SIZE_X; i++) {
        for (std::size_t j = 0; j < IMAGE_SIZE_Y; j++) {
            primitives::PrecisionType x =
                (primitives::PrecisionType)j * canvasSizeX/canvasWidth - canvasSizeX/2;
            primitives::PrecisionType y =
                canvasSizeY/2 - (primitives::PrecisionType)i * canvasSizeY/canvasHeight;
            primitives::Point3D pointOnCanvas;
            pointOnCanvas[0] = x;
            pointOnCanvas[1] = y;
            pointOnCanvas[2] = canvasZPosition;

            primitives::Vector3D rayDirection =
                math::Operations::normalise(pointOnCanvas - cameraOrigin);

            primitives::Ray r(cameraOrigin, rayDirection);

            (*canvas)[i][j] = world::Operations::colorAtIntersection(w, r);
        }
    }

    canvas->save("new_render_3_1080x1080_new.ppm");

    return 0;
}