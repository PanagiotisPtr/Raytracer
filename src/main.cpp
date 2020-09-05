#include <iostream>

#include "math/tensor.h"

int main() {
    math::Tensor<float, 2> m(3,4);
    std::cout << m << std::endl;
    return 0;
}