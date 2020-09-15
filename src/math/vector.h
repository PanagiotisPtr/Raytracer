#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <cstddef>
#include <ostream>
#include <iterator>
#include <initializer_list>

#include "exceptions.h"

namespace math {

template<typename T, std::size_t S>
class Vector : public std::array<T, S> {
public:
    using size_type = std::size_t;

    Vector() : std::array<T, S>({}) {}

    template<typename N>
    Vector(std::initializer_list<N> l) : std::array<T, S>({}) {
        if (l.size() != this->size())
            throw InitialiserListSizeException();

        size_type i = 0;
        for (const N& value : l)
            this->operator[](i++) = value;
    }

    template<typename N, std::size_t sz>
    friend std::ostream& operator<<(std::ostream& out, const Vector<N, sz>& v) {
        out << "[ ";
        for (const N& value : v)
            out << value << ", ";
        out << "]";

        return out;
    }
};

template<typename T>
using Vector3D = Vector<T, 3>;

} // namespace math

#endif