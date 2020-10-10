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

    // Matrix to Point
    template<typename T, std::size_t sz>
    static Point<T, sz> matrixToPoint(const Matrix<T, sz, 1>& m) {
        Point<T, sz> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i] = m[i][0];

        return rv;
    }

    // Matrix to Vector
    template<typename T, std::size_t sz>
    static Vector<T, sz> matrixToVector(const Matrix<T, sz, 1>& m) {
        Vector<T, sz> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i] = m[i][0];

        return rv;
    }
    
    // Matrix to Point
    template<typename T, std::size_t sz>
    static Point<T, sz> matrixToPoint(const Matrix<T, 1, sz>& m) {
        Point<T, sz> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i] = m[0][i];

        return rv;
    }

    // Matrix to Vector
    template<typename T, std::size_t sz>
    static Vector<T, sz> matrixToVector(const Matrix<T, 1, sz>& m) {
        Vector<T, sz> rv;

        for (std::size_t i = 0; i < sz; i++)
            rv[i] = m[0][i];

        return rv;
    }
};

} // namespace math

#endif