#ifndef PRIMITIVES_OPERATIONS_H
#define PRIMITIVES_OPERATIONS_H

#include <cmath>
#include <vector>

#include "intersection.h"
#include "intersection_container.h"
#include "ray.h"
#include "base_material.h"
#include "objects/sphere.h"
#include "objects/light.h"
#include "math/operations.h"
#include "math/utility.h"
#include "drawing/operations.h"

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

    static IntersectionContainer getRayObjectIntersections(const primitives::Ray& r, const objects::Object& o) {
        std::vector<PrecisionType> intersectionTimes = o.getRayIntersections(r);

        IntersectionContainer intersections;

        for (PrecisionType t : intersectionTimes) {
            intersections.addIntersection(primitives::Intersection(t, o));
        }

        return intersections;
    }

    static Vector3D getReflection(const Vector3D& v, const Vector3D& normal) {
        return v - (normal * (math::Operations::dotProduct(v, normal) * 2));
    }

    static drawing::Colour getColourOnSphere(
        const primitives::BaseMaterial& material,
        const objects::Light& light,
        const Point3D& intersection,
        const Vector3D& incoming,
        const Vector3D& normal,
        const bool inShadow = false
    ) {
        drawing::Colour baseColour = drawing::Operations::multiply(material.colour, light.getIntensity());
        Vector3D lightVector = math::Operations::normalise(light.getOrigin() - intersection);
        drawing::Colour ambient = drawing::Operations::multiply(baseColour, material.ambient);

        drawing::Colour diffuse = {0,0,0};
        drawing::Colour specular = {0,0,0};

        if (inShadow) {
            return ambient;
        }

        // check if light hits sphere
        primitives::PrecisionType test = math::Operations::dotProduct(lightVector, normal);
        if (test >= 0) {
            diffuse = drawing::Operations::multiply(drawing::Operations::multiply(baseColour, material.diffuse), test);

            Vector3D reflectVector = primitives::Operations::getReflection(Vector3D({0,0,0,0})-lightVector, normal);
            primitives::PrecisionType reflectionDot = math::Operations::dotProduct(reflectVector, incoming);
            if (reflectionDot > 0) {
                primitives::PrecisionType factor = std::pow(reflectionDot, material.shininess);
                specular = drawing::Operations::multiply(light.getIntensity(), (material.specular * factor));
            }
        }

        return drawing::Operations::add(drawing::Operations::add(ambient, diffuse), specular);
    }
};

} // namespace primitives

#endif