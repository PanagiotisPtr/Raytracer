#ifndef DRAWING_COLOUR_H
#define DRAWING_COLOUR_H

#include <cstddef>
#include <initializer_list>

#include "math/vector.h"

namespace drawing {

class Colour : public math::Vector<double, 3> {
public:
    Colour() : math::Vector<double, 3>() {}

    Colour(std::initializer_list<double> l) : math::Vector<double, 3>(l) {}

    double red() const { return this->operator[](0); }

    double green() const { return this->operator[](1); }

    double blue() const { return this->operator[](2); }

};

} // namespace drawing

#endif