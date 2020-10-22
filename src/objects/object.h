#ifndef OBJECTS_OBJECT_H
#define OBJECTS_OBJECT_H

#include "primitives/constants.h"
#include "primitives/material.h"
#include "primitives/base_material.h"
#include "math/matrix.h"
#include "math/operators.h"

namespace objects {

class Object {
public:
    Object()
    : transform(math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity()) {}

    void addTransformation(primitives::TransformationMatrix t) {
        this->transform = t * this->transform;
    }

    primitives::TransformationMatrix getTransformation() const { return this->transform; }

    primitives::BaseMaterial getMaterial() const { return this->material; }

    void setMaterial(primitives::BaseMaterial m) { this->material = m; }
protected:
    primitives::TransformationMatrix transform;
    primitives::BaseMaterial material;
};

} // namespace objects

#endif