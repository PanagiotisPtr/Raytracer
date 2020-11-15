#ifndef PRIMITIVES_INTERSECTION_H
#define PRIMITIVES_INTERSECTION_H

#include <functional>

#include "objects/object.h"
#include "primitives/constants.h"

namespace primitives {

struct Intersection {
    Intersection(PrecisionType t, const objects::Object& o) : time(t), target(o) {}

    PrecisionType time;
    const objects::Object& target;
};

struct IntersectionCompare {
    bool operator()(const Intersection& i1, const Intersection& i2) const {
        if (i1.time < 0 && i2.time < 0) {
            return i1.time > i2.time;
        } else if (i1.time < 0 && i2.time >= 0) {
            return false;
        } else if (i1.time >= 0 && i2.time < 0) {
            return true;
        }

        return i1.time < i2.time;
    }
};

} // namespace primitives

#endif