#ifndef PRIMITIVES_BASE_MATERIAL_H
#define PRIMITIVES_BASE_MATERIAL_H

#include "constants.h"
#include "material.h"
#include "drawing/colour.h"

namespace primitives {

struct BaseMaterial : public Material {
    BaseMaterial()
    : colour({1,1,1}), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0), reflective(0.0),
    transparency(0.0), refractiveIndex(1.0) {}

    BaseMaterial(drawing::Colour c, primitives::PrecisionType a, primitives::PrecisionType d,
                 primitives::PrecisionType sp, primitives::PrecisionType sh, primitives::PrecisionType r = 0.0,
                 primitives::PrecisionType t = 0.0, primitives::PrecisionType ri = 1.0)
    : colour(c), ambient(a), diffuse(d), specular(sp), shininess(sh),  reflective(r),
      transparency(t), refractiveIndex(ri) {}

    drawing::Colour colour;
    primitives::PrecisionType ambient;
    primitives::PrecisionType diffuse;
    primitives::PrecisionType specular;
    primitives::PrecisionType shininess;
    primitives::PrecisionType reflective;
    primitives::PrecisionType transparency;
    primitives::PrecisionType refractiveIndex;
};

} // namespace objects

#endif