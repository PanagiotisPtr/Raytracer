#ifndef PRIMITIVES_INTERSECTION_CONTAINER_H
#define PRIMITIVES_INTERSECTION_CONTAINER_H

#include <set>
#include <cstddef>

#include "intersection.h"

namespace primitives {

struct IntersectionContainer {
    // intersections in front of ray
    std::set<Intersection> front;

    // intersections behind of ray
    std::set<Intersection> back;

    void addIntersection(Intersection i) {
        if (i.time >= 0) {
            front.insert(i);
        } else {
            back.insert(i);
        }
    }

    std::size_t count() {
        return front.size() + back.size();
    }

    Intersection getFirst() { return *begin(front); }
};

} // namespace primitives

#endif