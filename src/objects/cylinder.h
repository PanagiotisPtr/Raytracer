#ifndef OBJECTS_CYLINDER_H
#define OBJECTS_CYLINDER_H

#include "object.h"
#include "primitives/constants.h"
#include "math/operations.h"
#include "math/utility.h"

namespace objects {

class Cylinder : public Object {
public:
    Cylinder() : Object() {}

    Cylinder(primitives::Point3D o) : Object(o) {}
protected:
    primitives::Vector3D getLocalNormalAt(const primitives::Point3D& p) const override {
        // hit top cap
        if (p[1] >= 1 - math::EQUALITY_DELTA && p[1] <= 1 + math::EQUALITY_DELTA) {
            return {0,1,0,0};
        }

        // hit bottom cap
        if (p[1] >= 0 && p[1] <= math::EQUALITY_DELTA) {
            return {0,-1,0,0};
        }

        // hit sides
        return p - primitives::Point3D({
            (primitives::PrecisionType)0,
            (primitives::PrecisionType)p[1],
            (primitives::PrecisionType)0,
            (primitives::PrecisionType)0
        });
    }

    std::vector<primitives::PrecisionType> getLocalRayIntersections(const primitives::Ray& r) const override {
        std::vector<primitives::PrecisionType> rv;

        primitives::PrecisionType x0 = r.getOrigin()[0];
        primitives::PrecisionType z0 = r.getOrigin()[2];

        primitives::PrecisionType vx = r.getDirection()[0];
        primitives::PrecisionType vz = r.getDirection()[2];

        if (math::EQUALITY_DELTA >= vx*vx + vz*vz && vx*vx + vz*vz >= 0) {
            return rv;
        }

        primitives::PrecisionType a = vx*vx + vz*vz;
        primitives::PrecisionType b = 2*vx*x0 + 2*vz*z0;
        primitives::PrecisionType c = x0*x0 + z0*z0 - 1;

        primitives::PrecisionType discriminant = b*b - (primitives::PrecisionType)4*a*c;

        if (discriminant < 0) {
            return rv;
        }

        primitives::PrecisionType t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        primitives::PrecisionType t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        bool t1Valid = this->validY(r.getOrigin(), r.getDirection(), t1);
        bool t2Valid = this->validY(r.getOrigin(), r.getDirection(), t2);

        if (t1Valid) {
            rv.push_back(t1);
        }

        if (t2Valid) {
            rv.push_back(t2);
        }

        std::vector<primitives::PrecisionType> caps = this->addCaps(
            r.getOrigin(),
            r.getDirection()
        );

        rv.insert(std::end(rv), std::begin(caps), std::end(caps));

        return rv;
    }
private:
    bool validY(
        const primitives::Point3D& o,
        const primitives::Vector3D& v,
        const primitives::PrecisionType& t
    ) const {
        if (v[1]*t + o[1] > 1 || v[1]*t + o[1] < 0) {
            return false;
        }
        
        return true;
    }

    bool validXZ(
        const primitives::Point3D& o,
        const primitives::Vector3D& v,
        const primitives::PrecisionType& t
    ) const {
        primitives::PrecisionType x = o[0] + v[0]*t;
        primitives::PrecisionType z = o[2] + v[2]*t;
        
        return (x*x + z*z) <= 1;
    }

    std::vector<primitives::PrecisionType> addCaps(
        const primitives::Point3D& o,
        const primitives::Vector3D& v
    ) const {
        std::vector<primitives::PrecisionType> rv;

        if (v[1] < math::EQUALITY_DELTA && v[1] > -math::EQUALITY_DELTA) {
            return rv;
        }

        primitives::PrecisionType t1 = (1 - o[1])/v[1];
        primitives::PrecisionType t2 = -o[1]/v[1];

        if (validXZ(o, v, t1)) {
            rv.push_back(t1);
        }

        if (validXZ(o, v, t2)) {
            rv.push_back(t2);
        }

        return rv;
    }
};

} // namespace objects

#endif