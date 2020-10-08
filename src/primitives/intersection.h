#ifndef PRIMITIVES_INTERSECTION_H
#define PRIMITIVES_INTERSECTION_H

#include "objects/object.h"
#include "primitives/constants.h"

namespace primitives {

struct Intersection {
    Intersection(PrecisionType t, objects::Object* o) : time(t), target(o) {}

    PrecisionType time;
    const objects::Object* target;
};

} // namespace primitives

#endif