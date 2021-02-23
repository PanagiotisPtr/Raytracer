#ifndef OBJECTS_PLANE_H
#define OBJECTS_PLANE_H

#include <vector>

#include "object.h"
#include "math/constants.h"

namespace objects {

class Plane : public Object {
public:
    Plane() : Object() {}

    Plane(primitives::Point3D o) : Object(o) {}
protected:
    primitives::Vector3D getLocalNormalAt(const primitives::Point3D& p) const override {
        // plane lies on the axis z and x so normal is always on y pointing up
        return primitives::Vector3D({0,1,0,0});
    }

    std::vector<primitives::PrecisionType> getLocalRayIntersections(const primitives::Ray& r) const override {
        // line is parallel to the plane (also avoid division by 0 later on)
        if (r.getDirection()[1] <= math::EQUALITY_DELTA) {
            return {};
        }
        // plane's y coordinate is 0.
        // y1 = y0 + ty => 0 = y0 + ty => y = -y0/y
        return { -r.getOrigin()[1]/r.getDirection()[1] };
    }
};

} // namespace objects

#endif