#ifndef OBJECTS_SPHERE_H
#define OBJECTS_SPHERE_H

#include "object.h"
#include "primitives/constants.h"
#include "math/operations.h"
#include "math/utility.h"

namespace objects {

class Sphere : public Object {
public:
    Sphere() : Object() {}

    Sphere(primitives::Point3D o) : Object(o) {}
protected:
    primitives::Vector3D getLocalNormalAt(const primitives::Point3D& p) const override {
        return p - primitives::Point3D({0,0,0,1});
    }

    std::vector<primitives::PrecisionType> getLocalRayIntersections(const primitives::Ray& r) const override {
        primitives::Vector3D sphereToRay = r.getOrigin() - this->getOrigin();

        // solve quadratic formula
        primitives::PrecisionType a = math::Operations::dotProduct(r.getDirection(), r.getDirection());
        primitives::PrecisionType b = 2 * math::Operations::dotProduct(r.getDirection(), sphereToRay);
        primitives::PrecisionType c = math::Operations::dotProduct(sphereToRay, sphereToRay) - 1;

        primitives::PrecisionType discriminant = b*b - (primitives::PrecisionType)4*a*c;

        if (discriminant < 0) {
            return {};
        }

        primitives::PrecisionType t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        primitives::PrecisionType t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        return {t1, t2};
    }
};

} // namespace objects

#endif