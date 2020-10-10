#ifndef OBJECTS_OBJECT_H
#define OBJECTS_OBJECT_H

#include "primitives/constants.h"
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
private:
    primitives::TransformationMatrix transform;
};

} // namespace objects

#endif