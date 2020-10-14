#ifndef DRAWING_CANVAS_H
#define DRAWING_CANVAS_H

#include <cstddef>
#include <initializer_list>
#include <fstream>
#include <string>
#include <algorithm>

#include "colour.h"
#include "math/matrix.h"

namespace drawing {

template<std::size_t Width, std::size_t Height>
using ColourMatrix = math::Matrix<Colour, Width, Height>;

template<std::size_t Width, std::size_t Height>
class Canvas : public ColourMatrix<Width, Height> {
public:
    Canvas() : ColourMatrix<Width, Height>() {}

    std::size_t getHeight() const { return Height; }
    
    std::size_t getWidth() const { return Width; }

    void save(const std::string& filename) {
        std::ofstream fout(filename);

        fout << "P3" << '\n';
        fout << Width << " " << Height << '\n';
        fout << 255 << '\n';

        for (std::size_t i = 0; i < Width; i++) {
            for (std::size_t j = 0; j < Height; j++) {
                // clamp colours to range (0, 255)
                Colour pixel = this->operator[](i)[j];
                int red = std::min(std::max(0.0, pixel.red()) * 255, 255.0);
                int green = std::min(std::max(0.0, pixel.green()) * 255, 255.0);
                int blue = std::min(std::max(0.0, pixel.blue()) * 255, 255.0);

                fout << red << ' ' << green << ' ' << blue << '\n';
            }
        }

        fout.close();
    }
};

} // namespace drawing

#endif