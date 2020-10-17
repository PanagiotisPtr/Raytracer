#ifndef PRIMITIVES_BASE_MATERIAL_H
#define PRIMITIVES_BASE_MATERIAL_H

#include "constants.h"
#include "material.h"
#include "drawing/colour.h"

namespace primitives {

struct BaseMaterial : public Material {
    BaseMaterial() : colour({1,1,1}), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0) {}

    BaseMaterial(drawing::Colour c, primitives::PrecisionType a, primitives::PrecisionType d,
                 primitives::PrecisionType sp, primitives::PrecisionType sh)
    : colour(c), ambient(a), diffuse(d), specular(sp), shininess(sh) {}

    drawing::Colour colour;
    primitives::PrecisionType ambient;
    primitives::PrecisionType diffuse;
    primitives::PrecisionType specular;
    primitives::PrecisionType shininess;
};

} // namespace objects

#endif