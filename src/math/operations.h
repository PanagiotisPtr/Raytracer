#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

#include <cstddef>
#include <initializer_list>
#include <cmath>

#include "vector.h"
#include "point.h"

namespace math {

class Operations {
public:
    /// Add vector to vector
    template<typename T, std::size_t sz>
    static Vector<T, sz> add(const Vector<T, sz>& v1, const Vector<T, sz>& v2) {
        Vector<T, sz> rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = v1[i] + v2[i];

        return rv;
    }

    /// Add vector to point
    template<typename T, std::size_t sz>
    static Point<T, sz> add(const Vector<T, sz>& v, const Point<T, sz>& p) {
        Point<T, sz> rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = v[i] + p[i];

        return rv;
    }

    /// Add point to vector
    template<typename T, std::size_t sz>
    static Point<T, sz> add(const Point<T, sz>& p, const Vector<T, sz>& v) {
        return Operations::add(v, p);
    }

    /// Subtract vector from vector
    template<typename T, std::size_t sz>
    static Vector<T, sz> subtract(const Vector<T, sz>& v1, const Vector<T, sz>& v2) {
        Vector<T, sz> rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = v1[i] - v2[i];

        return rv;
    }

    /// Subtract point from point
    template<typename T, std::size_t sz>
    static Vector<T, sz> subtract(const Point<T, sz>& p1, const Point<T, sz>& p2) {
        Vector<T, sz> rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = p1[i] - p2[i];

        return rv;
    }

    /// Subtract vector from point
    template<typename T, std::size_t sz>
    static Point<T, sz> subtract(const Point<T, sz>& p, const Vector<T, sz>& v) {
        Point<T, sz> rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = p[i] - v[i];

        return rv;
    }

    /// Multiplication
    template<
        typename T,
        std::size_t sz,
        typename VectorType,
        std::enable_if_t<
            std::is_same<VectorType, Vector<T, sz> >::value ||
            std::is_same<VectorType, Point<T, sz> >::value, int> = 0>
    static VectorType multiply(const VectorType& v, T c) {
        VectorType rv;
        for (std::size_t i = 0; i < sz; i++)
            rv[i] = v[i] * c;

        return rv;
    }

    template<
        typename T,
        std::size_t sz,
        typename VectorType,
        std::enable_if_t<
            std::is_same<VectorType, Vector<T, sz> >::value ||
            std::is_same<VectorType, Point<T, sz> >::value, int> = 0>
    static VectorType multiply(T c, const VectorType& v) {
        return Operations::multiply<T, sz>(v, c);
    }

    // Division
    template<
        typename T,
        std::size_t sz,
        typename VectorType,
        std::enable_if_t<
            std::is_same<VectorType, Vector<T, sz> >::value ||
            std::is_same<VectorType, Point<T, sz> >::value, int> = 0>
    static VectorType divide(const VectorType& v, T c) {
        return Operations::multiply<T, sz>(v, 1/c);
    }

    template<
        typename T,
        std::size_t sz,
        typename VectorType,
        std::enable_if_t<
            std::is_same<VectorType, Vector<T, sz> >::value ||
            std::is_same<VectorType, Point<T, sz> >::value, int> = 0>
    static VectorType divide(T c, const VectorType& v) {
        return Operations::divide<T, sz>(v, c);
    }

    // Magnitude
    template<typename T, std::size_t sz>
    static T magnitude(const Vector<T, sz>& v) {
        T sum = 0;
        for (std::size_t i = 0; i < sz; i++)
            sum += v[i]*v[i];
        
        return std::sqrt(sum);
    }

    // Normalisation
    template<typename T, std::size_t sz>
    static Vector<T, sz> normalise(const Vector<T, sz>& v) {
        T m = Operations::magnitude(v);

        return Operations::divide<T, sz>(v, m);
    }

    // Dot product
    template<typename T, std::size_t sz>
    static T dotProduct(const Vector<T, sz>& v1, const Vector<T, sz>& v2) {
        T rv = 0;
        for (std::size_t i = 0; i < sz; i++)
            rv += v1[i]*v2[i];
        
        return rv;
    }

    // Cross product (only defined for 3 dimensions)
    template<typename T>
    static Vector3D<T> crossProduct3D(const Vector3D<T>& v1, const Vector3D<T>& v2) {
        const T& x1 = v1[0];
        const T& y1 = v1[1];
        const T& z1 = v1[2];

        const T& x2 = v2[0];
        const T& y2 = v2[1];
        const T& z2 = v2[2];

        return Vector3D<T>({
            y1 * z2 - z1 * y2,
            z1 * x2 - x1 * z2,
            x1 * y2 - y1 * x2
        });
    }

};

} // namespace math

#endif