#ifndef OBJECTS_SPHERE_H
#define OBJECTS_SPHERE_H

#include "object.h"
#include "primitives/constants.h"

namespace objects {

class Sphere : public Object {
public:
    Sphere(primitives::Point3D o) : origin(o) {}

    primitives::Point3D getOrigin() { return this->origin; }
private:
    primitives::Point3D origin;
};

} // namespace objects

#endif