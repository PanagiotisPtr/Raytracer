#include <iostream>

#include "math/point.h"
#include "math/vector.h"
#include "math/matrix.h"

int main() {
    math::Point<int, 3> p = { 1, 2, 3 };

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

    std::cout << m << std::endl;

    return 0;
}