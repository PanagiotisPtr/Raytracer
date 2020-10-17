#ifndef OBJECTS_SPHERE_H
#define OBJECTS_SPHERE_H

#include "object.h"
#include "primitives/constants.h"
#include "primitives/material.h"
#include "primitives/base_material.h"

namespace objects {

class Sphere : public Object {
public:
    // Spheres have radius 1
    // To change the radius they need transformations
    Sphere(primitives::Point3D o)
    : origin(o) {}

    primitives::Point3D getOrigin() const { return this->origin; }

    primitives::BaseMaterial getMaterial() const { return this->material; }

    void setMaterial(primitives::BaseMaterial m) { this->material = m; }
private:
    primitives::Point3D origin;
    primitives::BaseMaterial material;
};

} // namespace objects

#endif