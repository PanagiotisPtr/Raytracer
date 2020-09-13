#include <iostream>

#include "math/tensor.h"

int main() {
    math::Tensor<float, 4> m(1,2,3,4);
    math::Tensor<size_t, 2> s = m.shape();
    s[0][0] = 1;
    std::cout << s << std::endl;
    m[0][0][1][1] = 4;
    std::cout << m << std::endl;
    return 0;
}