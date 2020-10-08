#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

#include <cstddef>
#include <initializer_list>
#include <cmath>

#include "vector.h"
#include "point.h"
#include "matrix.h"

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

    // Matrix multiplication
    template<typename T, std::size_t M, std::size_t N, std::size_t P>
    static Matrix<T, M, P> multiply(const Matrix<T, M, N>& m1, const Matrix<T, N, P>& m2) {
        Matrix<T, M, P> rv;

        for (std::size_t i = 0; i < M; i++) {
            for (std::size_t j = 0; j < P; j++) {
                rv[i][j] = 0;
                for (std::size_t k = 0; k < N; k++) {
                    rv[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }

        return rv;
    }

    // Matrix transopose
    template<typename T, std::size_t R, std::size_t C>
    static Matrix<T, C, R> transpose(const Matrix<T, R, C>& m) {
        Matrix<T, C, R> rv;
        
        for (std::size_t i = 0; i < R; i++) {
            for (std::size_t j = 0; j < C; j++) {
                rv[j][i] = m[i][j];
            }
        }

        return rv;
    }

    // Matrix determinant for 1x1 matrix
    template<typename T>
    static T determinant(const Matrix<T, 1, 1>& m) {
        return m[0][0];
    }

    // Matrix determinant
    template<typename T, std::size_t S>
    static T determinant(const Matrix<T, S, S>& m) {
        T rv = 0;
        for (std::size_t i = 0; i < S; i++) {
            rv += m[0][i] * minorAtIndex(m, 0, i) * cofactorSignAtIndex<T>(0, i);
        }

        return rv;
    }

    // Matrix inverse
    template<typename T, std::size_t S>
    static Matrix<T, S, S> inverse(const Matrix<T, S, S>& m) {
        const T d = determinant(m);

        if (std::isnan(d) || std::abs(d) <= EQUALITY_DELTA) {
            throw MatrixNotInvertableException();
        }

        Matrix<T, S, S> rv;
        for (std::size_t i = 0; i < S; i++) {
            for (std::size_t j = 0; j < S; j++) {
                rv[j][i] = (minorAtIndex(m, i, j) * cofactorSignAtIndex<T>(i, j)) / d;
            }
        }

        return rv;
    }

private:
    template<typename T>
    static T cofactorSignAtIndex(std::size_t i, std::size_t j) {
        return (i + j) % 2 ? -1 : 1;
    }

    template<typename T, std::size_t S>
    static T minorAtIndex(const Matrix<T, S, S>& m, std::size_t i, std::size_t j) {
        return determinant(m.submatrix(i, j));
    }
};

} // namespace math

#endif