#ifndef DRAWING_COLOUR_H
#define DRAWING_COLOUR_H

#include <cstddef>
#include <initializer_list>

#include "math/vector.h"

namespace drawing {

class Colour {
public:
    Colour() : data() {}

    Colour(std::initializer_list<double> l) : data(l) {}

    double red() const { return this->operator[](0); }

    double green() const { return this->operator[](1); }

    double blue() const { return this->operator[](2); }

    double& operator[](std::size_t idx) { return this->data[idx]; }

    const double& operator[](std::size_t idx) const { return this->data[idx]; }
private:
    math::Vector<double, 3> data;
};

} // namespace drawing

#endif