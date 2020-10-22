#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>

#include "../objects/sphere.h"
#include "../objects/light.h"
#include "../primitives/ray.h"
#include "../primitives/operations.h"
#include "../primitives/intersection_container.h"

namespace world {

// Currently world only allows sphere objects to be added
class World {
public:
    World() {}

    void addObject(objects::Sphere s) {
        objects.push_back(s);
    }

    void addObject(objects::Light l) {
        lights.push_back(l);
    }

    primitives::IntersectionContainer getIntersections(const primitives::Ray& r) const {
        primitives::IntersectionContainer c;
        for (const objects::Sphere& s : this->objects) {
            primitives::IntersectionContainer i =
                primitives::Operations::getRsaySphereIntersections(r, &s);
            c = primitives::Operations::mergeIntersectionContainers(c, i);
        }

        return c;
    }

    const std::vector<objects::Light> getLights() const { return this->lights; }
private:
    std::vector<objects::Sphere> objects;
    std::vector<objects::Light> lights;
};

} // namespace world

#endif