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

#define IMAGE_SIZE_X 1080
#define IMAGE_SIZE_Y 1080

int main() {
    primitives::Point3D cameraOrigin = {0,0,-2,1};
    auto canvas = (drawing::Canvas<IMAGE_SIZE_X, IMAGE_SIZE_Y>*)
        malloc(sizeof(drawing::Canvas<IMAGE_SIZE_X, IMAGE_SIZE_Y>));
    primitives::PrecisionType aspectRatio =
        (primitives::PrecisionType)IMAGE_SIZE_X/(primitives::PrecisionType)IMAGE_SIZE_Y;
    primitives::PrecisionType canvasSizeX = 10 * aspectRatio;
    primitives::PrecisionType canvasSizeY = 10;
    primitives::PrecisionType canvasWidth = IMAGE_SIZE_X;
    primitives::PrecisionType canvasHeight = IMAGE_SIZE_Y;
    objects::Sphere s({0,0,0,1});

    s.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(1.5,1.5,1.5)
    );
    
    for (std::size_t i = 0; i < IMAGE_SIZE_X; i++) {
        for (std::size_t j = 0; j < IMAGE_SIZE_Y; j++) {
            primitives::PrecisionType x =
                (primitives::PrecisionType)j * canvasSizeX/canvasWidth - canvasSizeX/2;
            primitives::PrecisionType y =
                canvasSizeY/2 - (primitives::PrecisionType)i * canvasSizeY/canvasHeight;
            primitives::Point3D pointOnCanvas;
            pointOnCanvas[0] = x;
            pointOnCanvas[1] = y;

            primitives::Vector3D rayDirection =
                math::Operations::normalise(pointOnCanvas - cameraOrigin);

            primitives::Ray r(cameraOrigin, rayDirection);

            primitives::IntersectionContainer intersections =
                primitives::Operations::getRsaySphereIntersections(r, &s);
            if (intersections.front.size() > 0) {
                (*canvas)[i][j] = drawing::Colour({1,1,1});
            } else {
                (*canvas)[i][j] = drawing::Colour({0,0,0});
            }
        }
    }

    canvas->save("render_3_1080x1080.ppm");

    return 0;
}