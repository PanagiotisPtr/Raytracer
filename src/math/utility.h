#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <cmath>

#include "vector.h"
#include "point.h"
#include "matrix.h"

namespace math {

class Utility {
public:
    // Point to matrix
    template<typename T, std::size_t sz>
    static Matrix<T, sz, 1> pointToMatrix(const Point<T, sz>& p) {
        Matrix<T, sz, 1> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i][0] = p[i];

        return rv;
    }

    // Vector to matrix
    template<typename T, std::size_t sz>
    static Matrix<T, sz, 1> vectorToMatrix(const Vector<T, sz>& v) {
        Matrix<T, sz, 1> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i][0] = v[i];

        return rv;
    }
};

} // namespace math

#endif