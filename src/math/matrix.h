#ifndef MATRIX_H
#define MATRIX_H

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

    template<typename N, std::size_t S1, std::size_t S2>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<N, S1, S2>& m) {
        out << "[ ";
        for (const Vector<N, S2>& value : m)
            out << value << ", ";
        out << "]";

        return out;
    }
};

} // namespace math

#endif