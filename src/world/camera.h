#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cmath>
#include <thread>
#include <mutex>
#include <queue>

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
private:
    struct RenderBlock {
        RenderBlock(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
        : start({x1, y1}), end({x2, y2}) {}

        RenderBlock() : start({0,0}), end({0,0}) {}

        math::Point<unsigned, 2> start; // top left
        math::Point<unsigned, 2> end; // bottom right
    };
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

    drawing::Canvas<Width, Height>* render(const World& w, unsigned blockSize = 64) {
        auto image = (drawing::Canvas<Width, Height>*)malloc(sizeof(drawing::Canvas<Width, Height>));
        const unsigned numberOfThreads = std::thread::hardware_concurrency();

        this->renderQueue = this->generateRenderBlocks(blockSize);


        std::queue<std::thread> pool;
        for (unsigned i = 0; i < numberOfThreads; i++) {
            pool.emplace([this](drawing::Canvas<Width, Height>* image, const World& w) {
                this->renderProcedure(image, std::cref(w));
            }, image, std::cref(w));
        }

        while (!pool.empty()) {
            pool.front().join();
            pool.pop();
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
    std::mutex renderQueueMutex;
    std::queue<RenderBlock> renderQueue;

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

    void renderProcedure(drawing::Canvas<Width, Height>* image, const World& w) {
        bool finished = false;
        RenderBlock block;

        do {
            std::unique_lock<std::mutex> guard(this->renderQueueMutex);
            if (this->renderQueue.empty()) {
                finished = true;
            } else {
                block = this->renderQueue.front();
                this->renderQueue.pop();
            }
            guard.unlock();

            if (! finished) {
                for (std::size_t y = block.start[1]; y < block.end[1]; y++) {
                    for (std::size_t x = block.start[0]; x < block.end[0]; x++) {
                        primitives::Ray r = this->getRayForPosition(x, y);
                        drawing::Colour c = Operations::colourAtIntersection(w, r);
                        // the image doesn't need locking because every thread writes
                        // in a different memory location
                        (*image)[y][x] = c;
                    }
                }
            }
        } while (!finished);
    }

    std::queue<RenderBlock> generateRenderBlocks(unsigned blockSize = 64) {
        const unsigned verticalBlocks = (Height + blockSize - 1) / blockSize;
        const unsigned horizontalBlocks = (Width + blockSize - 1) / blockSize;
        std::queue<RenderBlock> blocks;

        for (unsigned i = 0; i < verticalBlocks; i++) {
            for (unsigned j = 0; j < horizontalBlocks; j++) {
                // top left
                unsigned x1 = j * blockSize;
                unsigned y1 = i * blockSize;
                // bottom right
                unsigned x2 = (j+1) * blockSize > Width ? Width : (j+1) * blockSize;
                unsigned y2 = (i+1) * blockSize > Height ? Height : (i+1) * blockSize;

                blocks.emplace(x1, y1, x2, y2);
            }
        }

        return blocks;
    }
};

} // namespace world

#endif