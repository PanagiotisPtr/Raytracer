#ifndef DRAWING_COLOUR_H
#define DRAWING_COLOUR_H

#include <cstddef>
#include <initializer_list>

#include "math/vector.h"

namespace drawing {

class Colour : public math::Vector3D<double> {
public:
    Colour() : math::Vector3D<double>() {}

    Colour(std::initializer_list<double> l) : math::Vector3D<double>(l) {}
};

} // namespace drawing

#endif