#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include "math/point.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/operations.h"
#include "math/operators.h"
#include "math/transformations.h"

#include "drawing/colour.h"
#include "drawing/canvas.h"

#include "primitives/constants.h"
#include "primitives/ray.h"
#include "primitives/operations.h"

#include "objects/sphere.h"
#include "objects/light.h"
#include "objects/plane.h"
#include "objects/cube.h"
#include "objects/cylinder.h"

#include "world/world.h"
#include "world/camera.h"
#include "world/operations.h"

#define IMAGE_SIZE_X 1080
#define IMAGE_SIZE_Y 1080

std::vector<objects::Sphere> dogObjects() {
    std::vector<objects::Sphere> parts;
    primitives::BaseMaterial dogMaterial = primitives::BaseMaterial(
        drawing::Colour({0.72, 0.46, 0.29}),
        1,
        0.9,
        0.9,
        200.0
    );
    primitives::BaseMaterial eyeMaterial = primitives::BaseMaterial(
        drawing::Colour({0.1, 0.1, 0.1}),
        1,
        0.5,
        1.0,
        500.0
    );
    primitives::BaseMaterial noseMaterial = primitives::BaseMaterial(
        drawing::Colour({0.7, 0.2, 0.2}),
        1,
        0.5,
        1.0,
        500.0
    );

    objects::Sphere backRightLeg;
    backRightLeg.setMaterial(dogMaterial);

    backRightLeg.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(3.5,-0.2,0.0)
    );

    backRightLeg.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.2,0.5,0.2)
    );

    parts.push_back(backRightLeg);

    objects::Sphere frontRightLeg;
    frontRightLeg.setMaterial(dogMaterial);

    frontRightLeg.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-3.5,-0.2,0.0)
    );

    frontRightLeg.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.2,0.5,0.2)
    );

    parts.push_back(frontRightLeg);

    objects::Sphere backLeftLeg;
    backLeftLeg.setMaterial(dogMaterial);

    backLeftLeg.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(3.5,-0.2,-5)
    );

    backLeftLeg.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.2,0.5,0.2)
    );

    parts.push_back(backLeftLeg);

    objects::Sphere frontLeftLeg;
    frontLeftLeg.setMaterial(dogMaterial);

    frontLeftLeg.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-3.5,-0.2,-5)
    );

    frontLeftLeg.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.2,0.5,0.2)
    );

    parts.push_back(frontLeftLeg);

    objects::Sphere body;
    body.setMaterial(dogMaterial);

    body.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.0,0.8,-0.75)
    );

    body.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(1.2,0.6,0.75)
    );

    parts.push_back(body);

    objects::Sphere head;
    head.setMaterial(dogMaterial);

    head.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-2,1.5,-1.2)
    );

    head.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.5,0.5,0.5)
    );

    parts.push_back(head);

    objects::Sphere leftEye;
    leftEye.setMaterial(eyeMaterial);

    leftEye.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-14,9.5,-5)
    );

    leftEye.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.1,0.1,0.1)
    );

    parts.push_back(leftEye);

    objects::Sphere rightEye;
    rightEye.setMaterial(eyeMaterial);

    rightEye.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-13.5,9.5,-8)
    );

    rightEye.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.1,0.1,0.1)
    );

    parts.push_back(rightEye);

    objects::Sphere nose;
    nose.setMaterial(noseMaterial);

    nose.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-7.25,5.75,-5.5)
    );

    nose.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.2,0.125,0.125)
    );

    parts.push_back(nose);

    objects::Sphere leftEar;
    leftEar.setMaterial(dogMaterial);

    leftEar.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-5,2.5,-1.2)
    );

    leftEar.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.1,0.3,0.2)
    );

    leftEar.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(0.35)
    );

    leftEar.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-0.7,0.2,-0.4)
    );

    parts.push_back(leftEar);

    objects::Sphere rightEar;
    rightEar.setMaterial(dogMaterial);

    rightEar.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-5,2.5,-1.2)
    );

    rightEar.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.1,0.3,0.2)
    );

    rightEar.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(-0.35)
    );

    rightEar.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-0.7,0.3,-0.4)
    );

    parts.push_back(rightEar);

    return parts;
}

primitives::TransformationMatrix readTransformationMatrix(std::istream& in) {
    primitives::TransformationMatrix rv;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in >> rv[i][j];
            rv[i][j] *= 4;
        }
    }

    return rv;
}

primitives::BaseMaterial readMaterial(std::istream& in) {
    primitives::PrecisionType r, g, b;
    in >> r >> g >> b;

    return primitives::BaseMaterial(
        drawing::Colour({ (double)r, (double)g, (double)b }),
        1,
        0.5,
        1.0,
        500.0
    );
}

int main(int argc, char** argv) {
    std::vector<objects::Sphere> spheres;
    std::vector<objects::Cylinder> cylinders;
    std::vector<objects::Plane> planes;
    std::vector<objects::Cube> cubes;
    std::vector<objects::Light> lights;
    if (argc >= 2) {
        std::cout << argv[0] << std::endl;
        std::cout << argv[1] << std::endl;

        std::ifstream fin(argv[1]);

        if (!fin) {
            throw std::runtime_error("Failed to scene file");
        }

        std::string objectType = "";
        while (fin >> objectType) {
            std::cout << objectType << std::endl;
            if (objectType == "SPHERE") {
                spheres.push_back(objects::Sphere());
                spheres.back().setMaterial(readMaterial(fin));
                spheres.back().addTransformation(readTransformationMatrix(fin));
            }
            if (objectType == "CYLINDER") {
                cylinders.push_back(objects::Cylinder());
                cylinders.back().setMaterial(readMaterial(fin));
                cylinders.back().addTransformation(readTransformationMatrix(fin));
            }
            if (objectType == "PLANE") {
                planes.push_back(objects::Plane());
                planes.back().setMaterial(readMaterial(fin));
                planes.back().addTransformation(readTransformationMatrix(fin));
            }
            if (objectType == "CUBE") {
                cubes.push_back(objects::Cube());
                cubes.back().setMaterial(readMaterial(fin));
                cubes.back().addTransformation(readTransformationMatrix(fin));
            }
            if (objectType == "LIGHT") {
                readMaterial(fin);
                readTransformationMatrix(fin);
            }
            if (objectType == "CAMERA") {
                readMaterial(fin);
                readTransformationMatrix(fin);
            }
        }

        fin.close();
    }

    objects::Light l(
        drawing::Colour({ 1.0,1.0,1.0 }),
        primitives::Point3D({ -10,10,-10,1 })
    );

    world::World w;
    w.addObject(l);
    
    for (objects::Sphere& s : spheres) { w.addObject(s); }
    for (objects::Cylinder& s : cylinders) { w.addObject(s); }
    for (objects::Cube& s : cubes) { w.addObject(s); }
    for (objects::Plane& s : planes) { w.addObject(s); }
    for (objects::Light& s : lights) { w.addObject(s); }

    world::Camera<300, 200> camera(M_PI/3);
    camera.setTransformation(world::Operations::calculateCameraTransformation(
        primitives::Point3D({-3.75 * 3.0,2.0 * 3.0,-3.0 * 3.0,1.0}),
        primitives::Point3D({0,0,0,1}),
        primitives::Vector3D({0,1,0,1})
    ));
    auto image = camera.render(w);
    image->save("render.ppm");

    free(image);

    return 0;
}