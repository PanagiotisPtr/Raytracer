#ifndef MATH_OPERATORS_H
#define MATH_OPERATORS_H

#include "operations.h"

namespace math {

// addition
template<typename T, std::size_t sz>
Vector<T, sz> operator+(const Vector<T, sz>& v1, const Vector<T, sz>& v2) {
    return Operations::add(v1, v2);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator+(const Vector<T, sz>& v, const Point<T, sz>& p) {
    return Operations::add(v, p);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator+(const Point<T, sz>& p, const Vector<T, sz>& v) {
    return Operations::add(v, p);
}

// subtraction
template<typename T, std::size_t sz>
Vector<T, sz> operator-(const Vector<T, sz>& v1, const Vector<T, sz>& v2) {
    return Operations::subtract(v1, v2);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator-(const Point<T, sz>& p1, const Point<T, sz>& p2) {
    return Operations::subtract(p1, p2);
}

template<typename T, std::size_t sz>
Point<T, sz> operator-(const Point<T, sz>& p, const Vector<T, sz>& v) {
    return Operations::subtract(p, v);
}

// multiplication
template<typename T, std::size_t sz>
Point<T, sz> operator*(const Point<T, sz>& p, T c) {
    return Operations::multiply<T, sz>(p, c);
}

template<typename T, std::size_t sz>
Point<T, sz> operator*(T c, const Point<T, sz>& p) {
    return Operations::multiply<T, sz>(p, c);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator*(const Vector<T, sz>& v, T c) {
    return Operations::multiply<T, sz>(v, c);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator*(T c, const Vector<T, sz>& v) {
    return Operations::multiply<T, sz>(v, c);
}

// division
template<typename T, std::size_t sz>
Point<T, sz> operator/(const Point<T, sz>& p, T c) {
    return Operations::divide<T, sz>(p, c);
}

template<typename T, std::size_t sz>
Point<T, sz> operator/(T c, const Point<T, sz>& p) {
    return Operations::divide<T, sz>(p, c);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator/(const Vector<T, sz>& v, T c) {
    return Operations::divide<T, sz>(v, c);
}

template<typename T, std::size_t sz>
Vector<T, sz> operator/(T c, const Vector<T, sz>& v) {
    return Operations::divide<T, sz>(v, c);
}

} // namespace math

#endif