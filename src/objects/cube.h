#ifndef OBJECTS_CUBE_H
#define OBJECTS_CUBE_H

#include <vector>

#include "object.h"
#include "math/constants.h"

namespace objects {

class Cube : public Object {
public:
    Cube() : Object() {}

    Cube(primitives::Point3D o) : Object(o) {}
protected:
    primitives::Vector3D getLocalNormalAt(const primitives::Point3D& p) const override {
        primitives::PrecisionType absX = p[0] > 0 ? p[0] : -p[0];
        primitives::PrecisionType absY = p[1] > 0 ? p[1] : -p[1];
        primitives::PrecisionType absZ = p[2] > 0 ? p[2] : -p[2];

        if (absX > absY && absX > absZ) {
            return {
                    p[0],
                    (primitives::PrecisionType)0.0,
                    (primitives::PrecisionType)0.0,
                    (primitives::PrecisionType)0.0
                };
        } else if (absY > absX && absY > absZ) {
            return {
                    (primitives::PrecisionType)0.0,
                    p[1],
                    (primitives::PrecisionType)0.0,
                    (primitives::PrecisionType)0.0
                };
        }

        return {
            (primitives::PrecisionType)0.0,
            (primitives::PrecisionType)0.0,
            p[2],
            (primitives::PrecisionType)0.0
        };
    }

    std::vector<primitives::PrecisionType> getLocalRayIntersections(const primitives::Ray& r) const override {
        primitives::PrecisionType tx1 = (1 - r.getOrigin()[0]) / r.getDirection()[0];
        primitives::PrecisionType tx2 = (-1 - r.getOrigin()[0]) / r.getDirection()[0];
        if (tx1 > tx2) {
            std::swap(tx1, tx2);
        }

        primitives::PrecisionType ty1 = (1 - r.getOrigin()[1]) / r.getDirection()[1];
        primitives::PrecisionType ty2 = (-1 - r.getOrigin()[1]) / r.getDirection()[1];
        if (ty1 > ty2) {
            std::swap(ty1, ty2);
        }

        primitives::PrecisionType tz1 = (1 - r.getOrigin()[2]) / r.getDirection()[2];
        primitives::PrecisionType tz2 = (-1 - r.getOrigin()[2]) / r.getDirection()[2];
        if (tz1 > tz2) {
            std::swap(tz1, tz2);
        }

        primitives::PrecisionType tmin = std::max(std::max(tx1, ty1), tz1);
        primitives::PrecisionType tmax = std::min(std::min(tx2, ty2), tz2);

        if (tmin > tmax) {
            return {};
        }

        return {tmin, tmax};
    }
};

} // namespace objects

#endif