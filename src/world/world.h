#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>
#include <functional>

#include "objects/object.h"
#include "objects/light.h"
#include "primitives/ray.h"
#include "primitives/operations.h"
#include "primitives/intersection_container.h"

namespace world {

class World {
public:
    using constObjectReference = std::reference_wrapper<const objects::Object>;
    using constLightReference = std::reference_wrapper<const objects::Light>;

    World() {}

    void addObject(const objects::Object& o) {
        objects.push_back(std::cref(o));
    }

    void addObject(const objects::Light& l) {
        lights.push_back(std::cref(l));
    }

    primitives::IntersectionContainer getIntersections(const primitives::Ray& r) const {
        primitives::IntersectionContainer c;
        for (const objects::Object& o : this->objects) {
            primitives::IntersectionContainer i =
                primitives::Operations::getRayObjectIntersections(r, o);
            c = primitives::Operations::mergeIntersectionContainers(c, i);
        }

        return c;
    }

    const std::vector<constObjectReference> getObjects() const { return this->objects; }

    const std::vector<constLightReference> getLights() const { return this->lights; }
private:
    std::vector<constObjectReference> objects;
    std::vector<constLightReference> lights;
};

} // namespace world

#endif