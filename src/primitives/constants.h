#ifndef PRIMITIVES_CONSTANTS_H
#define PRIMITIVES_CONSTANTS_H

#include "math/point.h"
#include "math/vector.h"

namespace primitives {

using PrecisionType = long double;

using Point3D = math::Point<PrecisionType, 4>;

using Vector3D = math::Vector<PrecisionType, 4>;

using TransformationMatrix = math::Matrix<PrecisionType, 4, 4>;

} // namespace primitives

#endif