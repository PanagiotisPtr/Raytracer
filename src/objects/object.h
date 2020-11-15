#ifndef OBJECTS_OBJECT_H
#define OBJECTS_OBJECT_H

#include <vector>

#include "primitives/constants.h"
#include "primitives/material.h"
#include "primitives/base_material.h"
#include "primitives/ray.h"
#include "math/matrix.h"
#include "math/operations.h"
#include "math/operators.h"
#include "math/utility.h"

namespace objects {

class Object {
public:
    Object()
    : origin({0,0,0,1}), transform(math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity()) {}

    Object(primitives::Point3D o)
    : origin(o), transform(math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity()) {}

    virtual ~Object() {}

    void addTransformation(primitives::TransformationMatrix t) {
        this->transform = t * this->transform;
    }

    primitives::Point3D getOrigin() const { return this->origin; }

    primitives::TransformationMatrix getTransformation() const { return this->transform; }

    primitives::BaseMaterial getMaterial() const { return this->material; }

    void setMaterial(primitives::BaseMaterial m) { this->material = m; }

    virtual primitives::Vector3D getNormalAt(const primitives::Point3D& p) const {
        primitives::Point3D local = math::Utility::matrixToPoint(
            math::Operations::inverse(this->getTransformation()) * math::Utility::pointToMatrix(p)
        );
        primitives::Vector3D localNormal = this->getLocalNormalAt(local);
        primitives::Vector3D worldNormal = math::Utility::matrixToVector(
            math::Operations::transpose(math::Operations::inverse(this->getTransformation()))
            * math::Utility::vectorToMatrix(localNormal)
        );
        worldNormal[3] = 0;

        return math::Operations::normalise(worldNormal);
    }

    virtual std::vector<primitives::PrecisionType> getRayIntersections(const primitives::Ray& r) const {
        return this->getLocalRayIntersections(this->rayToLocal(r));
    }

protected:
    primitives::Point3D origin;
    primitives::TransformationMatrix transform;
    primitives::BaseMaterial material;

    virtual primitives::Vector3D getLocalNormalAt(const primitives::Point3D& p) const = 0;

    virtual std::vector<primitives::PrecisionType> getLocalRayIntersections(const primitives::Ray& r) const = 0;

private:
    primitives::Ray rayToLocal(const primitives::Ray& r) const {
        primitives::Vector3DMatrix originMatrix = math::Utility::pointToMatrix(r.getOrigin());
        primitives::Vector3DMatrix directionMatrix = math::Utility::vectorToMatrix(r.getDirection());

        primitives::TransformationMatrix inverseTransformation = math::Operations::inverse(this->transform);

        primitives::Vector3DMatrix newOriginMatrix = inverseTransformation * originMatrix;
        primitives::Vector3DMatrix newDirectionMatrix = inverseTransformation * directionMatrix;

        primitives::Point3D newOrigin = math::Utility::matrixToPoint(newOriginMatrix);
        primitives::Vector3D newDirection = math::Utility::matrixToVector(newDirectionMatrix);

        return primitives::Ray(newOrigin, newDirection);
    }
};

} // namespace objects

#endif