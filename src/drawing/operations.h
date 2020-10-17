#ifndef DRAWING_OPERATIONS_H
#define DRAWING_OPERATIONS_H

#include <cstddef>
#include <initializer_list>
#include <cmath>

#include "colour.h"
#include "math/vector.h"
#include "math/operations.h"

namespace drawing {

class Operations {
public:
    static math::Vector<double, 3> colourToVector(const Colour& c) {
        return math::Vector<double, 3>({
            c[0],
            c[1],
            c[2]
        });
    }

    static Colour vectorToColour(const math::Vector<double, 3>& v) {
        return Colour({
            v[0],
            v[1],
            v[2]
        });
    }

    static Colour add(const Colour& c1, const Colour& c2) {
        math::Vector<double, 3> rv = math::Operations::add(
            colourToVector(c1),
            colourToVector(c2)
        );

        return vectorToColour(rv);
    }

    static Colour subtract(const Colour& c1, const Colour& c2) {
        math::Vector<double, 3> rv = math::Operations::subtract(
            colourToVector(c1),
            colourToVector(c2)
        );

        return vectorToColour(rv);
    }

    static Colour multiply(const Colour& c1, const Colour& c2) {
        return Colour({
            c1[0] * c2[0],
            c1[1] * c2[1],
            c1[2] * c2[2]
        });
    }

    template<typename T>
    static Colour multiply(T s, const Colour& c) {
        return Colour({
            c[0] * (double)s,
            c[1] * (double)s,
            c[2] * (double)s
        });
    }

    template<typename T>
    static Colour multiply(const Colour& c, T s) {
        return Operations::multiply(s, c);
    }

    template<typename T>
    static Colour divide(const Colour& c, T s) {
        return Operations::multiply(1/s, c);
    }

    template<typename T>
    static Colour divide(T s, const Colour& c) {
        return Operations::multiply(1/s, c);
    }
};

} // namespace drawing

#endif