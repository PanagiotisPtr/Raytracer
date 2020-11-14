#ifndef PRIMITIVES_RAY_H
#define PRIMITIVES_RAY_H

#include "constants.h"
#include "math/operators.h"

namespace primitives {

class Ray {
public:
    Ray(Point3D o, Vector3D d) : origin(o), direction(d) {}

    Point3D getOrigin() const { return this->origin; }

    Vector3D getDirection() const { return this->direction; }

    Point3D getAtTime(PrecisionType t) const {
        return this->origin + (this->direction * t);
    }

private:
    Point3D origin;
    Vector3D direction;
};

} // namespace primitives

#endif