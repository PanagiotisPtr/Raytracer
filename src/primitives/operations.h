#ifndef PRIMITIVES_OPERATIONS_H
#define PRIMITIVES_OPERATIONS_H

#include <cmath>

#include "intersection.h"
#include "intersection_container.h"
#include "ray.h"
#include "objects/sphere.h"
#include "math/operations.h"
#include "math/utility.h"

namespace primitives {

class Operations {
public:
    // merge intersection containers
    // make sure the ray has the same origin
    // for the merge to be valid
    static IntersectionContainer mergeIntersectionContainers(
        IntersectionContainer c1,
        IntersectionContainer c2
    ) {
        IntersectionContainer c3;
        for (Intersection i : c1.front) {
            c3.addIntersection(i);
        }
        for (Intersection i : c2.front) {
            c3.addIntersection(i);
        }

        for (Intersection i : c1.back) {
            c3.addIntersection(i);
        }
        for (Intersection i : c2.back) {
            c3.addIntersection(i);
        }

        return c3;
    }

    static Ray transformRay(const Ray& r, const primitives::TransformationMatrix& m) {
        primitives::Vector3DMatrix originMatrix = math::Utility::pointToMatrix(r.getOrigin());
        primitives::Vector3DMatrix directionMatrix = math::Utility::vectorToMatrix(r.getDirection());

        primitives::Vector3DMatrix newOriginMatrix = m * originMatrix;
        primitives::Vector3DMatrix newDirectionMatrix = m * directionMatrix;

        primitives::Point3D newOrigin = math::Utility::matrixToPoint(newOriginMatrix);
        primitives::Vector3D newDirection = math::Utility::matrixToVector(newDirectionMatrix);

        return Ray(newOrigin, newDirection);
    }

    static IntersectionContainer getRsaySphereIntersections(const primitives::Ray ray, const objects::Sphere* s) {
        IntersectionContainer intersections;

        primitives::Ray r = transformRay(
            ray,
            math::Operations::inverse(s->getTransformation())
        );

        Vector3D sphereToRay = r.getOrigin() - s->getOrigin();

        // solve quadratic formula
        PrecisionType a = math::Operations::dotProduct(r.getDirection(), r.getDirection());
        PrecisionType b = 2 * math::Operations::dotProduct(r.getDirection(), sphereToRay);
        PrecisionType c = math::Operations::dotProduct(sphereToRay, sphereToRay) - 1;

        PrecisionType discriminant = b*b - (PrecisionType)4*a*c;

        if (discriminant < 0) {
            return intersections;
        }

        PrecisionType t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        PrecisionType t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        intersections.addIntersection(Intersection(t1, s));
        intersections.addIntersection(Intersection(t2, s));

        return intersections;
    }
};

} // namespace primitives

#endif