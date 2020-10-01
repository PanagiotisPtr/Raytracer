#ifndef MATH_POINT_H
#define MATH_POINT_H

#include <cstddef>
#include <initializer_list>

#include "vector.h"

namespace math {

template<typename T, std::size_t S>
class Point : public Vector<T, S> {
public:
    Point() : Vector<T,S>() {}

    template<typename N>
    Point(std::initializer_list<N> l) : Vector<T, S>(l) {}
};

} // namespace math

#endif