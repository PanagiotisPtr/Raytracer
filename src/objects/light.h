#ifndef OBJECTS_LIGHT_H
#define OBJECTS_LIGHT_H

#include "object.h"
#include "primitives/constants.h"
#include "drawing/colour.h"

namespace objects {

class Light : public Object {
public:
    Light(drawing::Colour i, primitives::Point3D o)
    : intensity(i), origin(o) {}

    primitives::Point3D getOrigin() const { return this->origin; }

    drawing::Colour getIntensity() const { return this->intensity; }
private:
    drawing::Colour intensity;
    primitives::Point3D origin;
};

} // namespace objects

#endif