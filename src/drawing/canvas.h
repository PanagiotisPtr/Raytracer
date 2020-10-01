#ifndef DRAWING_CANVAS_H
#define DRAWING_CANVAS_H

#include <cstddef>
#include <initializer_list>

#include "colour.h"
#include "math/matrix.h"

namespace drawing {

template<std::size_t Width, std::size_t Height>
using ColourMatrix = math::Matrix<Colour, Width, Height>;

template<std::size_t Width, std::size_t Height>
class Canvas : public ColourMatrix<Width, Height> {
public:
    Canvas() : ColourMatrix<Width, Height>() {}
};

} // namespace drawing

#endif