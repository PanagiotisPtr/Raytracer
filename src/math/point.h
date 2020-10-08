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

template<typename T>
class Point3D : public Point<T, 4> {
public:
    Point3D() : Point<T, 4>({(T)0,(T)0,(T)0,(T)1}) {}

    Point3D(T x, T y, T z) : Point<T, 4>({x,y,z,(T)1}) {}

    T& x() { return this->operator[](0); }

    T& y() { return this->operator[](1); }

    T& z() { return this->operator[](2); }
};

} // namespace math

#endif