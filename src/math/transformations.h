#ifndef MATH_TRANSFORMATIONS_H
#define MATH_TRANSFORMATIONS_H

#include <cmath>

#include "matrix.h"

namespace math {

// Only 3D transformations are supported
// Points are assumed to have 3 dimensions
// and an extra one as a placeholder (allows
// for translation)
class Transformations {
public:
    template<typename T>
    static Matrix<T, 4, 4> translate(T x, T y, T z) {
        Matrix<T, 4, 4> rv = Matrix<T, 4, 4>::getIdentity();

        rv[0][3] = x;
        rv[1][3] = y;
        rv[2][3] = z;

        return rv;
    }

    template<typename T>
    static Matrix<T, 4, 4> scale(T x, T y, T z) {
        Matrix<T, 4, 4> rv = Matrix<T, 4, 4>::getIdentity();

        rv[0][0] = x;
        rv[1][1] = y;
        rv[2][2] = z;

        return rv;
    }

    // Get rotation matrix for x axis rotation
    // theta given in radians
    template<typename T>
    static Matrix<T, 4, 4> rotateX(T theta) {
        Matrix<T, 4, 4> rv = Matrix<T, 4, 4>::getIdentity();

        rv[1][1] = std::cos(theta);
        rv[2][1] = std::sin(theta);
        rv[1][2] = -std::sin(theta);
        rv[2][2] = std::cos(theta);

        return rv;
    }

    // Get rotation matrix for y axis rotation
    // theta given in radians
    template<typename T>
    static Matrix<T, 4, 4> rotateY(T theta) {
        Matrix<T, 4, 4> rv = Matrix<T, 4, 4>::getIdentity();

        rv[0][0] = std::cos(theta);
        rv[2][0] = -std::sin(theta);
        rv[0][2] = std::sin(theta);
        rv[2][2] = std::cos(theta);

        return rv;
    }

    // Get rotation matrix for z axis rotation
    // theta given in radians
    template<typename T>
    static Matrix<T, 4, 4> rotateZ(T theta) {
        Matrix<T, 4, 4> rv = Matrix<T, 4, 4>::getIdentity();

        rv[0][0] = std::cos(theta);
        rv[1][0] = std::sin(theta);
        rv[0][1] = -std::sin(theta);
        rv[1][1] = std::cos(theta);

        return rv;
    }
};

} // namespace math

#endif