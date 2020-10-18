#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <array>
#include <cstddef>
#include <ostream>
#include <iterator>
#include <initializer_list>

#include "exceptions.h"
#include "constants.h"

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

    bool operator==(const Vector<T, S>& v) const {
        for (std::size_t i = 0; i < S; i++) {
            const T& a = v[i];
            const T& b = this->operator[](i);
            if (a > b && a - b > EQUALITY_DELTA)
                return false;
            else if (b - a > EQUALITY_DELTA)
                return false;
        }

        return true;
    }

    bool operator!=(const Vector<T, S>& v) const {
        return !((*this) == v);
    }
};

template<typename N, std::size_t sz>
std::ostream& operator<<(std::ostream& out, const Vector<N, sz>& v) {
    out << "[ ";
    for (const N& value : v)
        out << value << ", ";
    out << "]";

    return out;
}

} // namespace math

#endif