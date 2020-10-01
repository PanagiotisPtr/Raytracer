#ifndef DRAWING_OPERATORS_H
#define DRAWING_OPERATORS_H

#include "operations.h"

namespace drawing {

Colour operator+(const Colour& c1, const Colour& c2) {
    return Operations::add(c1, c2);
}

Colour operator-(const Colour& c1, const Colour& c2) {
    return Operations::subtract(c1, c2);
}

Colour operator*(const Colour& c1, const Colour& c2) {
    return Operations::multiply(c1, c2);
}

template<typename T>
Colour operator*(T s, const Colour& c) {
    return Operations::multiply(s, c);
}

template<typename T>
Colour operator*(const Colour& c, T s) {
    return Operations::multiply(s, c);
}

template<typename T>
Colour operator/(const Colour& c, T s) {
    return Operations::divide(s, c);
}

template<typename T>
Colour operator/(const Colour& c, T s) {
    return Operations::divide(s, c);
}

} // namespace drawing

#endif