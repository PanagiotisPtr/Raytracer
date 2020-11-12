#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#include <cmath>

#include "drawing/canvas.h"
#include "primitives/constants.h"
#include "primitives/ray.h"
#include "math/operators.h"
#include "math/utility.h"
#include "world.h"
#include "operations.h"

namespace world {

template<std::size_t Width, std::size_t Height>
class Camera {
public:
    Camera() : frameHeight(Height), frameWidth(Width) {
        this->transform = primitives::TransformationMatrix::getIdentity();
    }

    template<typename T>
    Camera(T fov)
    : frameHeight(Height), frameWidth(Width), fieldOfView(fov) {
        this->transform = primitives::TransformationMatrix::getIdentity();
    }

    // setters

    template<typename T>
    void setFielfOfView(T fov) const { this->fieldOfView = (primitives::PrecisionType)fov; }

    void setTransformation(primitives::TransformationMatrix t) { this->transform = t; }

    void addTransformation(primitives::TransformationMatrix t) {
        this->transform = t * this->transform;
    }

    // getters

    primitives::PrecisionType getFielfOfView() const { return this->fieldOfView; }

    primitives::TransformationMatrix getTransformation() const { return this->transform; }

    primitives::Ray getRayForPosition(std::size_t pixelX, std::size_t pixelY) {
        primitives::PrecisionType viewWidth = this->getViewWidth();
        primitives::PrecisionType viewHeight = this->getViewHeight();
        primitives::PrecisionType pixelSize = this->getPixelSize();

        primitives::PrecisionType x = pixelX;
        primitives::PrecisionType y = pixelY;

        // we add 0.5 to go to the center of the pixel
        primitives::PrecisionType offsetX = (x + 0.5) * pixelSize;
        primitives::PrecisionType offsetY = (y + 0.5) * pixelSize;

        primitives::PrecisionType worldX = (viewWidth/2) - offsetX;
        primitives::PrecisionType worldY = (viewHeight/2) - offsetY;

        primitives::Point3D worldPoint;
        worldPoint[0] = worldX;
        worldPoint[1] = worldY;
        worldPoint[2] = -1;
        worldPoint[3] = 1;

        primitives::Point3D pixel = math::Utility::matrixToPoint(
            math::Operations::inverse(this->transform) * math::Utility::pointToMatrix(worldPoint)
        );
        primitives::Point3D origin = math::Utility::matrixToPoint(
            math::Operations::inverse(this->transform) * math::Utility::pointToMatrix(primitives::Point3D({0,0,0,1}))
        );
        primitives::Vector3D direction = math::Operations::normalise(pixel - origin);

        return primitives::Ray(origin, direction);
    }

    drawing::Canvas<Width, Height>* render(const World& w) {
        auto image = new drawing::Canvas<Width, Height>();

        for (std::size_t y = 0; y < Height; y++) {
            for (std::size_t x = 0; x < Width; x++) {
                primitives::Ray r = this->getRayForPosition(x, y);
                drawing::Colour c = Operations::colorAtIntersection(w, r);
                (*image)[y][x] = c;
            }
        }

        return image;
    }

    primitives::PrecisionType getAspectRatio() {
        return this->frameWidth / this->frameHeight;
    }
private:
    primitives::PrecisionType frameHeight;
    primitives::PrecisionType frameWidth;
    primitives::PrecisionType fieldOfView;
    primitives::TransformationMatrix transform;

    primitives::PrecisionType getViewWidth() {
        primitives::PrecisionType aspectRatio = this->getAspectRatio();
        primitives::PrecisionType viewSize = 2 * std::tan(this->fieldOfView / 2);

        if (aspectRatio >= 1) {
            return viewSize;
        }

        return viewSize * aspectRatio;
    }

    primitives::PrecisionType getViewHeight() {
        primitives::PrecisionType aspectRatio = this->getAspectRatio();
        primitives::PrecisionType viewSize = 2 * std::tan(this->fieldOfView / 2);

        if (aspectRatio >= 1) {
            return viewSize / aspectRatio;
        }

        return viewSize;
    }

    primitives::PrecisionType getPixelSize() {
        return this->getViewWidth() / this->frameWidth;
    }
};

} // namespace world

#endif