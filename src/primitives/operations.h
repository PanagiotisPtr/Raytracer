#ifndef PRIMITIVES_OPERATIONS_H
#define PRIMITIVES_OPERATIONS_H

#include <cmath>

#include "intersection.h"
#include "intersection_container.h"
#include "ray.h"
#include "objects/sphere.h"
#include "math/operations.h"

namespace primitives {

class Operations {

    // merge intersection containers
    // make sure the ray has the same origin
    // for the merge to be valid
    IntersectionContainer mergeIntersectionContainers(
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

    IntersectionContainer getRsaySphereIntersections(Ray r, objects::Sphere* s) {
        IntersectionContainer intersections;

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