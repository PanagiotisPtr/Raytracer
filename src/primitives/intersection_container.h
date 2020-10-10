#ifndef PRIMITIVES_INTERSECTION_CONTAINER_H
#define PRIMITIVES_INTERSECTION_CONTAINER_H

#include <set>
#include <cstddef>

#include "intersection.h"
#include "exceptions.h"

namespace primitives {

struct IntersectionContainer {
    // intersections in front of ray
    std::set<Intersection, IntersectionCompare> front;

    // intersections behind of ray
    std::set<Intersection, IntersectionCompare> back;

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

    // throw exception if front is empty
    Intersection getFirst() const {
        if (front.size() == 0) {
            throw NoIntersectionsException();
        }

        return *std::begin(front);
    }
};

} // namespace primitives

#endif