#ifndef OBJECTS_PLANE_H
#define OBJECTS_PLANE_H

#include <vector>
#include <cmath>
#include <math.h>

#include "object.h"
#include "cube.h"
#include "math/constants.h"
#include "math/transformations.h"

namespace objects {

class Plane : public Cube {
public:
    Plane() : Cube() {
        this->addTransformation(
            math::Transformations::scale<primitives::PrecisionType>(1.0, 0.001, 1.0)
        );
    }

    Plane(primitives::Point3D o) : Cube(o) {
        this->addTransformation(
            math::Transformations::scale<primitives::PrecisionType>(1.0, 0.001, 1.0)
        );
    }
};

} // namespace objects

#endif