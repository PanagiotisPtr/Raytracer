#ifndef WORLD_OPERATIONS_H
#define WORLD_OPERATIONS_H

#include <cmath>

#include "drawing/colour.h"
#include "primitives/ray.h"
#include "primitives/intersection_container.h"
#include "primitives/constants.h"
#include "primitives/operations.h"
#include "objects/light.h"
#include "math/operations.h"
#include "math/transformations.h"
#include "math/constants.h"
#include "world.h"

namespace world {

class Operations {
public:
    static drawing::Colour colorAtIntersection(const World& w, const primitives::Ray& r) {
        primitives::IntersectionContainer c = w.getIntersections(r);
        drawing::Colour finalColour({0,0,0});

        try {
            primitives::Intersection first = c.getFirst();
            for (const objects::Light& l : w.getLights()) {
                primitives::Point3D p = r.getAtTime(first.time);
                const objects::Object* object = first.target;
                primitives::Vector3D rayDirection = math::Operations::normalise(r.getDirection());
                primitives::Vector3D in = primitives::Vector3D({0,0,0,0}) - rayDirection;
                primitives::Vector3D normal = object->getNormalAt(p);
                bool inside = math::Operations::dotProduct(normal, in) < 0 ? true : false;
                bool inShadow = Operations::shadowed(p, l, w);

                if (inside) {
                    normal = primitives::Vector3D({0,0,0,0}) - normal;
                }

                drawing::Colour colour =
                    primitives::Operations::getColourOnSphere(object->getMaterial(), l, p, in, normal, inShadow);

                finalColour = drawing::Operations::add(finalColour, colour);
            }
        } catch(const primitives::NoIntersectionsException& e) {
            return finalColour;
        }

        return finalColour;
    }

    // This actually calculates the transformation the world needs
    // so that it looks like the camera moved.
    static primitives::TransformationMatrix calculateCameraTransformation(
        primitives::Point3D position,
        primitives::Point3D target,
        primitives::Vector3D up
    ) {
        // need to compute new
        // standard basis vectors
        primitives::TransformationMatrix t = primitives::TransformationMatrix::getIdentity();
        
        primitives::Vector3D front = math::Operations::normalise(target - position);

        math::Vector<primitives::PrecisionType, 3> front3;
        front3[0] = front[0];
        front3[1] = front[1];
        front3[2] = front[2];

        math::Vector<primitives::PrecisionType, 3> up3;
        up3[0] = up[0];
        up3[1] = up[1];
        up3[2] = up[2];

        primitives::Vector3D left;
        math::Vector<primitives::PrecisionType, 3> left3 = math::Operations::crossProduct3D(
            front3,
            math::Operations::normalise(up3)
        );
        left[0] = left3[0];
        left[1] = left3[1];
        left[2] = left3[2];
        left[3] = 0;

        primitives::Vector3D orthogonalUp;
        math::Vector<primitives::PrecisionType, 3> orthogonalUp3 = math::Operations::crossProduct3D(
            left3,
            front3
        );
        orthogonalUp[0] = orthogonalUp3[0];
        orthogonalUp[1] = orthogonalUp3[1];
        orthogonalUp[2] = orthogonalUp3[2];
        orthogonalUp[3] = 0;

        t[0] = left;
        t[1] = orthogonalUp;
        t[2] = primitives::Vector3D({0,0,0,0}) - front;

        return t * math::Transformations::translate(-position[0], -position[1], -position[2]);
    }
private:
    static bool shadowed(const primitives::Point3D& p, const objects::Light& l, const World& w) {
        primitives::Vector3D v = l.getOrigin() - p;
        primitives::PrecisionType distanceToLight = math::Operations::magnitude(v);
        v = math::Operations::normalise(v);
        primitives::Point3D movedP = p + (v * (primitives::PrecisionType)math::EQUALITY_DELTA);

        primitives::Ray r(movedP, v);
        primitives::IntersectionContainer c = w.getIntersections(r);

        try {
            primitives::Intersection first = c.getFirst();
            if (first.time < distanceToLight) {
                return true;
            }
        } catch (const primitives::NoIntersectionsException& e) {
            return false;
        }

        return false;
    }
};

} // namespace primitives

#endif