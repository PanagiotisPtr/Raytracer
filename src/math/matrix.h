#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <array>
#include <cstddef>
#include <ostream>
#include <iterator>

#include "vector.h"

namespace math {

template<typename T, std::size_t R, std::size_t C>
class Matrix : public std::array<Vector<T, C>, R> {
public:
    using row_type = Vector<T, C>;
    using size_type = std::size_t;

    Matrix() : std::array<Vector<T, C>, R>({}) {}

    template<typename N>
    Matrix(std::initializer_list<std::initializer_list<N> > l)
    : std::array<Vector<T, C>, R>({}) {
        if (l.size() != this->size())
            throw InitialiserListSizeException();

        size_type i = 0;
        for (const std::initializer_list<N>& value : l)
            this->operator[](i++) = value;
    }

    static Matrix<T, R, R> getIdentity() {
        Matrix<T, R, R> rv;

        for (std::size_t i = 0; i < R; i++) {
            for (std::size_t j = 0; j < R; j++) {
                rv[i][j] = i == j ? 1 : 0;
            }
        }

        return rv;
    }

    Matrix<T, R-1, C-1> submatrix(std::size_t r, std::size_t c) const {
        Matrix<T, R-1, C-1> rv;

        for (std::size_t i = 0; i < R; i++) {
            if (i == r) {
                continue;
            }

            for (std::size_t j = 0; j < C; j++) {
                if (j == c) {
                    continue;
                }

                rv[i - (i > r)][j - (j > c)] = this->operator[](i)[j];
            }
        }

        return rv;
    }

    bool operator==(const Matrix<T, R, C>& m) const {
        for (std::size_t i = 0; i < R; i++)
            if (m[i] != this->operator[](i))
                return false;

        return true;
    }

    bool operator!=(const Matrix<T, R, C>& m) const {
        return !((*this) == m);
    }
};

template<typename N, std::size_t S1, std::size_t S2>
std::ostream& operator<<(std::ostream& out, const Matrix<N, S1, S2>& m) {
    out << "[ ";
    for (const Vector<N, S2>& value : m)
        out << value << ", ";
    out << "]";

    return out;
}

} // namespace math

#endif