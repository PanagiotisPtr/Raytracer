#ifndef PRIMITIVES_RAY_H
#define PRIMITIVES_RAY_H

#include "constants.h"
#include "intersection.h"
#include "intersection_container.h"
#include "math/operators.h"

namespace primitives {

class Ray {
public:
    Ray(Point3D o, Vector3D d) : origin(o), direction(d) {}

    Point3D getOrigin() { return this->origin; }

    Vector3D getDirection() { return this->direction; }

    Point3D getAtTime(PrecisionType t) {
        return this->origin + (this->direction * t);
    }

private:
    Point3D origin;
    Vector3D direction;
    IntersectionContainer intersections;
};

} // namespace primitives

#endif