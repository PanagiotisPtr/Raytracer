#ifndef WORLD_OPERATIONS_H
#define WORLD_OPERATIONS_H

#include <cmath>

#include "../drawing/colour.h"
#include "../drawing/operators.h"
#include "../primitives/ray.h"
#include "../primitives/intersection_container.h"
#include "../primitives/constants.h"
#include "../primitives/operations.h"
#include "../objects/light.h"
#include "../math/operations.h"
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
                const objects::Object object = *(first.target);
                primitives::Vector3D rayDirection = math::Operations::normalise(r.getDirection());
                primitives::Vector3D in = primitives::Vector3D({0,0,0,0}) - rayDirection;
                primitives::Vector3D normal = primitives::Operations::getSphereNormalAtPoint(object, p);
                bool inside = math::Operations::dotProduct(normal, in) < 0 ? true : false;

                if (inside) {
                    normal = primitives::Vector3D({0,0,0,0}) - normal;
                }

                drawing::Colour colour =
                    primitives::Operations::getColourOnSphere(object.getMaterial(), l, p, in, normal);

                finalColour = finalColour + colour;
            }
        } catch(const primitives::NoIntersectionsException& e) {
            return finalColour;
        }

        return finalColour;
    }
};

} // namespace primitives

#endif