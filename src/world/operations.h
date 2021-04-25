#ifndef WORLD_OPERATIONS_H
#define WORLD_OPERATIONS_H

#include <cmath>
#include <functional>

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
    static drawing::Colour colourAtIntersection(const World& w, const primitives::Ray& r, const unsigned bounces = 5) {
        if (bounces == 0) {
            return drawing::Colour({0,0,0});
        }

        primitives::IntersectionContainer c = w.getIntersections(r);
        drawing::Colour finalColour({0,0,0});

        try {
            primitives::Intersection first = c.getFirst();
            for (const objects::Light& l : w.getLights()) {
                primitives::Point3D p = r.getAtTime(first.time);
                const objects::Object& object = first.target;
                primitives::Vector3D rayDirection = math::Operations::normalise(r.getDirection());
                primitives::Vector3D in = primitives::Vector3D({0,0,0,0}) - rayDirection;
                primitives::Vector3D normal = object.getNormalAt(p);
                bool inside = math::Operations::dotProduct(normal, in) < 0 ? true : false;
                bool inShadow = Operations::shadowed(p, l, w);

                if (inside) {
                    normal = primitives::Vector3D({0,0,0,0}) - normal;
                }

                // std::cout << "MyRay: " << r.getOrigin() << "\t" << r.getDirection() << std::endl;
                // std::cout << "Intersected at: " << p << "\t\tRemaining: " << bounces << std::endl;
                // std::cout << "At time: " << first.time << std::endl;

                drawing::Colour colour =
                    primitives::Operations::getColourOnObject(object.getMaterial(), l, p, in, normal, inShadow);

                drawing::Colour refractedColour({0,0,0});
                drawing::Colour reflectedColour({0,0,0});
                primitives::PrecisionType reflectancePercent = 0;

                if (object.getMaterial().transparency > 0) {
                    // std::cout << "Is transparent" << std::endl;
                    std::pair<primitives::PrecisionType, primitives::PrecisionType> refractiveIndexes =
                        primitives::Operations::getRefractiveIndexes(c, object);
                    if (inside) {
                        std::swap(refractiveIndexes.first, refractiveIndexes.second);
                    }
                    
                    // std::cout << "Refractive indexes: eta1: " << refractiveIndexes.first << "\teta2: " << refractiveIndexes.second << std::endl; 
                    primitives::PrecisionType ratio = refractiveIndexes.first / refractiveIndexes.second;
                    primitives::PrecisionType cosTheta1 = math::Operations::dotProduct(
                        in,
                        normal
                    );
                    primitives::PrecisionType sinTheta2Squared = (ratio * ratio) * (1 - cosTheta1*cosTheta1);

                    // std::cout << "sinTheta2Squared: " << sinTheta2Squared << std::endl;

                    if (sinTheta2Squared < 1) {
                        primitives::Ray refracted = primitives::Operations::getRefractedRay(
                            refractiveIndexes.first,
                            refractiveIndexes.second,
                            p,
                            in,
                            normal
                        );

                        // std::cout << "Shooting refracted ray from point: " << refracted.getOrigin() << "\t at direction" << refracted.getDirection() << std::endl;

                        refractedColour = Operations::colourAtIntersection(w, refracted, bounces - 1);
                        refractedColour = drawing::Operations::multiply(refractedColour, object.getMaterial().transparency);

                        if (object.getMaterial().reflective > 0) {
                            reflectancePercent = primitives::Operations::getReflectancePercent(
                                refractiveIndexes.first,
                                refractiveIndexes.second,
                                in,
                                normal
                            );
                        }
                    }
                } else {
                    // std::cout << "Isn't transparent. Colour is: " << colour.red() << '\t' << colour.green() << '\t' << colour.blue() << std::endl;
                }

                // check if reflective
                if (object.getMaterial().reflective > 0 && !inside) {
                    primitives::Vector3D reflectedVector =
                        primitives::Operations::getReflection(primitives::Vector3D({0,0,0,0})-in, normal);
                    primitives::Ray reflectedRay(
                        // Move point slightly up towards its normal vector to avoid self interactions
                        p + (normal * (primitives::PrecisionType)math::EQUALITY_DELTA),
                        reflectedVector
                    );

                    // std::cout << "Shooting reflection ray..." << std::endl;
                    reflectedColour = Operations::colourAtIntersection(w, reflectedRay, bounces - 1);
                }

                finalColour = drawing::Operations::add(finalColour, colour);
                if (object.getMaterial().reflective > 0 && object.getMaterial().transparency > 0) {
                    refractedColour = drawing::Operations::multiply(refractedColour, 1 - reflectancePercent);
                    reflectedColour = drawing::Operations::multiply(reflectedColour, reflectancePercent);
                }

                finalColour = drawing::Operations::add(refractedColour, finalColour);
                finalColour = drawing::Operations::add(reflectedColour, finalColour);
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