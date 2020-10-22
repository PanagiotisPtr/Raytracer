#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#include "../primitives/constants.h"
#include "../math/operators.h"

namespace world {

class Camera {
public:
    Camera() {
        this->transform = primitives::TransformationMatrix::getIdentity();
    }

    template<typename T>
    Camera(T fh, T fw, T fov)
    : frameHeight(fh), frameWidth(fw), fieldOfView(fov) {
        this->transform = primitives::TransformationMatrix::getIdentity();
    }

    // setters

    template<typename T>
    void setFrameHeight(T fh) const { this->frameHeight = (primitives::PrecisionType)fh; }

    template<typename T>
    void setFrameWidth(T fw) const { this->frameWidth = (primitives::PrecisionType)fw; }

    template<typename T>
    void setFielfOfView(T fov) const { this->fieldOfView = (primitives::PrecisionType)fov; }

    void setTransformation(primitives::TransformationMatrix t) { this->transform = t; }

    void addTransformation(primitives::TransformationMatrix t) {
        this->transform = t * this->transform;
    }

    // getters

    primitives::PrecisionType getFrameHeight() const { return this->frameHeight; }

    primitives::PrecisionType getFrameWidth() const { return this->frameWidth; }

    primitives::PrecisionType getFielfOfView() const { return this->fieldOfView; }

    primitives::TransformationMatrix getTransformation() const { return this->transform; }
private:
    primitives::PrecisionType frameHeight;
    primitives::PrecisionType frameWidth;
    primitives::PrecisionType fieldOfView;
    primitives::TransformationMatrix transform;
};

} // namespace world

#endif