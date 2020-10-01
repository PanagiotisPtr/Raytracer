#include <iostream>

#include "math/point.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/operations.h"
#include "math/operators.h"
#include "drawing/colour.h"
#include "drawing/canvas.h"

int main() {
    math::Point<float, 5> p = { 1, 2, 3, 4, 5 };

    std::cout << p << std::endl;

    math::Vector<float, 5> v = { 4, 5, 6, 7, 8};
    for (std::size_t i = 0; i < v.size(); i++) {break;
        v[i] = i+1;
    }

    std::cout << v << std::endl;

    math::Matrix<float, 3, 3> m = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    math::Matrix<float, 3, 3> k = {
        {1.00001f, 2.00001f, 3.00001f},
        {4.00001f, 5.00001f, 6.00001f},
        {7.00001f, 8.00001f, 9.00001f}
    };

    std::cout << m << std::endl;

    auto vp = math::Operations::add(v, p);

    std::cout << vp << std::endl;

    auto vv = v + v;

    auto qq = math::Operations::multiply<float, 5>(vv, 10);

    std::cout << vv << std::endl;

    std::cout << qq/5.0f << std::endl;

    std::cout << (vv == ((qq/5.0f)/2.0f)) << std::endl;

    std::cout << (p == p) << std::endl;

    std::cout << (m == k) << std::endl;

    drawing::Colour c1 = {1, 2, 3};
    drawing::Colour c2 = {255,255,255};

    drawing::Canvas<1, 2> canv1;
    canv1[0][0] = c1;
    canv1[0][1] = c2;

    canv1[0][1] = {255, 0, 0};

    std::cout << c1 << std::endl;

    std::cout << c2 << std::endl;

    std::cout << canv1 << std::endl;


    return 0;
}