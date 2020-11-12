#ifndef PRIMITIVES_OPERATIONS_H
#define PRIMITIVES_OPERATIONS_H

#include <cmath>

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

    static Vector3D getSphereNormalAtPoint(const objects::Object& s, const Point3D& p) {
        Point3D local = math::Utility::matrixToPoint(
            math::Operations::inverse(s.getTransformation()) * math::Utility::pointToMatrix(p)
        );
        Vector3D localNormal = local - Point3D({0,0,0,1});
        Vector3D worldNormal = math::Utility::matrixToVector(
            math::Operations::transpose(math::Operations::inverse(s.getTransformation()))
            * math::Utility::vectorToMatrix(localNormal)
        );
        worldNormal[3] = 0;

        return math::Operations::normalise(worldNormal);
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