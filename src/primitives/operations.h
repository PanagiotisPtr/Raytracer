#ifndef PRIMITIVES_OPERATIONS_H
#define PRIMITIVES_OPERATIONS_H

#include <cmath>
#include <vector>
#include <iterator>

#include "intersection.h"
#include "intersection_container.h"
#include "objects/object.h"
#include "ray.h"
#include "referenceContainer.h"
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

    static IntersectionContainer getRayObjectIntersections(const Ray& r, const objects::Object& o) {
        std::vector<PrecisionType> intersectionTimes = o.getRayIntersections(r);

        IntersectionContainer intersections;

        for (PrecisionType t : intersectionTimes) {
            intersections.addIntersection(Intersection(t, o));
        }

        return intersections;
    }

    static Vector3D getReflection(const Vector3D& v, const Vector3D& normal) {
        return v - (normal * (math::Operations::dotProduct(v, normal) * 2));
    }

    static drawing::Colour getColourOnObject(
        const BaseMaterial& material,
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

        // check if light hits object
        PrecisionType test = math::Operations::dotProduct(lightVector, normal);
        if (test >= 0) {
            diffuse = drawing::Operations::multiply(drawing::Operations::multiply(baseColour, material.diffuse), test);

            Vector3D reflectVector = Operations::getReflection(Vector3D({0,0,0,0})-lightVector, normal);
            PrecisionType reflectionDot = math::Operations::dotProduct(reflectVector, incoming);
            if (reflectionDot > 0) {
                PrecisionType factor = std::pow(reflectionDot, material.shininess);
                specular = drawing::Operations::multiply(light.getIntensity(), (material.specular * factor));
            }
        }

        return drawing::Operations::add(drawing::Operations::add(ambient, diffuse), specular);
    }

    static std::pair<PrecisionType, PrecisionType> getRefractiveIndexes(
        const IntersectionContainer& intersectionsContainer,
        const objects::Object& target
    ) {
        PrecisionType in = 1.0;
        PrecisionType out = 1.0;

        ReferenceContainer<objects::Object> container;
        std::set<Intersection, IntersectionCompare> intersections(intersectionsContainer.back);
        intersections.insert(std::begin(intersectionsContainer.front), std::end(intersectionsContainer.front));

        for (const Intersection& i : intersections) {
            if (&target == &i.target) {
                if (container.size()) {
                    in = container.getLast().getMaterial().refractiveIndex;
                }
            }

            if (container.contains(i.target)) {
                container.remove(i.target);
            } else {
                container.add(i.target);
            }

            if (&target == &i.target) {
                if (container.size()) {
                    out = container.getLast().getMaterial().refractiveIndex;
                }

                break;
            }
        }

        return std::pair<PrecisionType, PrecisionType>({in, out});
    }

    static Ray getRefractedRay(
        const PrecisionType& eta1,
        const PrecisionType& eta2,
        const Point3D& intersection,
        const Vector3D& rayDirection,
        const Vector3D& normal
    ) {
        PrecisionType ratio = eta1 / eta2;
        PrecisionType cosTheta1 = math::Operations::dotProduct(rayDirection, normal);
        PrecisionType sinTheta2Squared = (ratio * ratio) * (1 - cosTheta1*cosTheta1);

        // std::cout << "Normal: " << normal << std::endl;

        // std::cout << "cosTheta1: " << cosTheta1 << std::endl;

        PrecisionType cosTheta2 = sqrt(1 - sinTheta2Squared);
        Vector3D direction =
            normal * (ratio * cosTheta1 - cosTheta2) - (rayDirection * ratio);
        
        Point3D belowIntersection =
            intersection - (normal * (PrecisionType)math::EQUALITY_DELTA);

        return Ray(belowIntersection, direction);
    }

    static PrecisionType getReflectancePercent(
        const PrecisionType& eta1,
        const PrecisionType& eta2,
        const Vector3D& rayDirection,
        const Vector3D& normal
    ) {
        PrecisionType cos = math::Operations::dotProduct(
            math::Operations::normalise(rayDirection),
            math::Operations::normalise(normal)
        );

        // Check case where normal is flipped
        if (cos < 0) {
            cos = math::Operations::dotProduct(
                math::Operations::normalise(rayDirection),
                math::Operations::normalise(Vector3D({0,0,0,0}) - normal)
            );
        }

        if (eta1 > eta2) {
            PrecisionType ratio = eta1 / eta2;
            PrecisionType check = (ratio * ratio) * (1 - cos * cos);
            if (check > 1) {
                return 1;
            }

            PrecisionType cosTheta2 = sqrt(1 - check);
            cos = cosTheta2;
        }

        PrecisionType r0 = (eta1 - eta2) / (eta1 + eta2);
        r0 = r0 * r0;

        PrecisionType result = r0 + (1 - r0) * std::pow(1 - cos, 5);

        return result;
    }
};

} // namespace primitives

#endif