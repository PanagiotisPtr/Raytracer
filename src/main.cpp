#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include <cassert>

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

void renderCoverImage() {
    objects::Light l(
        drawing::Colour({ 1.0,1.0,1.0 }),
        primitives::Point3D({ -10,10,-10,1 })
    );

    world::World w;
    w.addObject(l);

    objects::Sphere sphere;
    objects::Cylinder cylinder;
    objects::Cube cube;
    objects::Plane right;
    objects::Plane floor;

    right.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(1.4, 0.6, 1.0)
    );
    
    floor.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(10.0, 10.0, 10.0)
    );

    floor.setMaterial(primitives::BaseMaterial(
        drawing::Colour({ (double)0.1, (double)0.5, (double)0.1 }),
        1,
        0.5,
        0.1,
        500.0,
        0.0,
        0.0,
        1.0
    ));

    right.setMaterial(primitives::BaseMaterial(
        drawing::Colour({ (double)0.1, (double)0.1, (double)0.1 }),
        0.5,
        0.6,
        1.0,
        500.0,
        1.0,
        0.0,
        1.0
    ));

    right.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(M_PI / 2)
    );

    right.addTransformation(
        math::Transformations::rotateY<primitives::PrecisionType>(M_PI / 8)
    );

    right.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.0, 1.0, 2.0)
    );

    sphere.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.4, 0.4, 0.4)
    );

    sphere.setMaterial(primitives::BaseMaterial(
        drawing::Colour({ (double)1.0, (double)0.0, (double)0.4 }),
        1,
        0.5,
        1.0,
        2000.0,
        0.0,
        0.0,
        1.0
    ));

    sphere.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(0.0, 0.4, 0.0)
    );

    cube.setMaterial(primitives::BaseMaterial(
        drawing::Colour({ (double)0.0, (double)0.3, (double)0.8 }),
        1,
        0.5,
        0.3,
        500.0,
        0.3,
        0.5,
        1.0
    ));

    cube.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.3, 0.3, 0.3)
    );

    cube.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(1.5, -0.2, -1.2)
    );

    cube.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(M_PI / 4)
    );

    cube.addTransformation(
        math::Transformations::rotateY<primitives::PrecisionType>(M_PI / 4)
    );

    cube.addTransformation(
        math::Transformations::rotateZ<primitives::PrecisionType>(M_PI / 4)
    );

    cylinder.setMaterial(primitives::BaseMaterial(
        drawing::Colour({ (double)0.4, (double)0.0, (double)0.8 }),
        0.8,
        0.8,
        0.6,
        500.0,
        0.8,
        0.0,
        1.0
    ));

    cylinder.addTransformation(
        math::Transformations::scale<primitives::PrecisionType>(0.3, 1.0, 0.3)
    );

    cylinder.addTransformation(
        math::Transformations::rotateX<primitives::PrecisionType>(M_PI / 2)
    );

    cylinder.addTransformation(
        math::Transformations::rotateY<primitives::PrecisionType>(M_PI / 4)
    );

    cylinder.addTransformation(
        math::Transformations::translate<primitives::PrecisionType>(-2.0, 0.33, -0.4)
    );

    cylinder.addTransformation(
        math::Transformations::rotateY<primitives::PrecisionType>(M_PI / 4)
    );

    w.addObject(floor);
    w.addObject(right);
    w.addObject(sphere);
    w.addObject(cube);
    w.addObject(cylinder);

    world::Camera<1920, 1080> camera(M_PI/3);
    camera.setTransformation(world::Operations::calculateCameraTransformation(
        primitives::Point3D({-3.75, 1.4, -3.0, 1.0}),
        primitives::Point3D({0.0,0.5,0.0,1.0}),
        primitives::Vector3D({0,1,0,1})
    ));
    auto image = camera.render(w);
    image->save("render.ppm");

    free(image);
}

primitives::BaseMaterial readMaterialFromInstructions(std::istream& in) {
    double red,green,blue,a,d,sp,sh,r,t,ri;

    std::string op;
    while (in >> op) {
        if (op == "END") {
            in >> op;
            return primitives::BaseMaterial(drawing::Colour({red,green,blue}),a,d,sp,sh,r,t,ri);
        }
        if (op == "COLOUR") in >> red >> green >> blue;
        if (op == "AMBIENT") in >> a;
        if (op == "DIFFUSE") in >> d;
        if (op == "SPECULAR") in >> sp;
        if (op == "SHININESS") in >> sh;
        if (op == "REFLECTIVITY") in >> r;
        if (op == "TRANSPARENCY") in >> t;
        if (op == "RI") in >> ri;
    }

    return primitives::BaseMaterial(drawing::Colour({red,green,blue}),a,d,sp,sh,r,t,ri);
}

primitives::TransformationMatrix readTransformationsFromInstructions(std::istream& in) {
    primitives::TransformationMatrix rv =
        math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity();
    
    double x, y, z, r;
    std::string op;
    while (in >> op) {
        if (op == "END") {
            in >> op;
            return rv;
        }
        if (op == "SCALE") {
            in >> x >> y >> z;
            rv = math::Transformations::scale<primitives::PrecisionType>(x, y, z) * rv;
        }
        if (op == "TRANSLATE") {
            in >> x >> y >> z;
            rv = math::Transformations::translate<primitives::PrecisionType>(x, y, z) * rv;
        }
        if (op == "ROTATE_X") {
            in >> r;
            rv = math::Transformations::rotateX<primitives::PrecisionType>(r) * rv;
        }
        if (op == "ROTATE_Y") {
            in >> r;
            rv = math::Transformations::rotateY<primitives::PrecisionType>(r) * rv;
        }
        if (op == "ROTATE_Z") {
            in >> r;
            rv = math::Transformations::rotateZ<primitives::PrecisionType>(r) * rv;
        }
    }

    return rv;
}

void runInstructionsFile(char* filename) {
    std::vector<objects::Sphere> spheres;
    std::vector<objects::Cylinder> cylinders;
    std::vector<objects::Plane> planes;
    std::vector<objects::Cube> cubes;
    std::vector<objects::Light> lights;
    world::Camera<1280, 720> camera(M_PI/3);
    world::World w;

    std::ifstream fin(filename);
    std::string ins;

    fin >> ins;
    if (ins != "OUTPUT_FILE") {
        std::cout << "First line must contain OUTPUT_FILE instruction" << std::endl;
        return;
    }
    std::string outputFilename; fin >> outputFilename;

    while (fin >> ins) {
        if (ins != "START") {
            std::cout << "Expected 'START', found " << ins << std::endl;
            fin.close();

            return;
        }
        std::string type; fin >> type;
        if (type == "CAMERA") {
            primitives::Point3D location;
            primitives::Point3D lookat;
            location[3] = 1.0;

            std::string op;
            while (fin >> op) {
                if (op == "END") {
                    fin >> op;
                    break;
                }
                if (op == "LOCATION") {
                    fin >> location[0] >> location[1] >> location[2];
                }
                if (op == "LOOK_AT") {
                    fin >> lookat[0] >> lookat[1] >> lookat[2];
                }
            }

            camera.setTransformation(world::Operations::calculateCameraTransformation(
                location,
                lookat,
                primitives::Vector3D({0,1,0,1})
            ));
        } else if (type == "LIGHT") {
            drawing::Colour colour;
            primitives::Point3D location;
            location[3] = 1.0;

            std::string op;
            while (fin >> op) {
                if (op == "END") {
                    fin >> op;
                    break;
                }
                if (op == "LOCATION") {
                    fin >> location[0] >> location[1] >> location[2];
                }
                if (op == "COLOUR") {
                    double r,g,b; fin >> r >> g >> b;
                    colour = drawing::Colour({r,g,b});
                }
            }

            lights.push_back(objects::Light(colour, location));
        } else if (type == "OBJECT") {
            std::string name; fin >> name;
            if (name == "PLANE") {
                primitives::BaseMaterial material;
                primitives::TransformationMatrix transform
                    = math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity();
                
                std::string op; fin >> op;
                while (fin >> op) {
                    if (op == "END") {
                        fin >> op;
                        break;
                    }
                    if (op == "MATERIAL") {
                        material = readMaterialFromInstructions(fin);
                    }
                    if (op == "TRANSFORMATION") {
                        transform = readTransformationsFromInstructions(fin);
                    }
                }

                objects::Plane p;
                p.setMaterial(material);
                p.addTransformation(transform);
                planes.push_back(p);
            }
            if (name == "SPHERE") {
                primitives::BaseMaterial material;
                primitives::TransformationMatrix transform
                    = math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity();
                
                std::string op; fin >> op;
                while (fin >> op) {
                    if (op == "END") {
                        fin >> op;
                        break;
                    }
                    if (op == "MATERIAL") {
                        material = readMaterialFromInstructions(fin);
                    }
                    if (op == "TRANSFORMATION") {
                        transform = readTransformationsFromInstructions(fin);
                    }
                }

                objects::Sphere s;
                s.setMaterial(material);
                s.addTransformation(transform);
                spheres.push_back(s);
            }
            if (name == "CUBE") {
                primitives::BaseMaterial material;
                primitives::TransformationMatrix transform
                    = math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity();
                
                std::string op; fin >> op;
                while (fin >> op) {
                    if (op == "END") {
                        fin >> op;
                        break;
                    }
                    if (op == "MATERIAL") {
                        material = readMaterialFromInstructions(fin);
                    }
                    if (op == "TRANSFORMATION") {
                        transform = readTransformationsFromInstructions(fin);
                    }
                }

                objects::Cube c;
                c.setMaterial(material);
                c.addTransformation(transform);
                cubes.push_back(c);
            }
            if (name == "CYLINDER") {
                primitives::BaseMaterial material;
                primitives::TransformationMatrix transform
                    = math::Matrix<primitives::PrecisionType, 4, 4>::getIdentity();
                
                std::string op; fin >> op;
                while (fin >> op) {
                    if (op == "END") {
                        fin >> op;
                        break;
                    }
                    if (op == "MATERIAL") {
                        material = readMaterialFromInstructions(fin);
                    }
                    if (op == "TRANSFORMATION") {
                        transform = readTransformationsFromInstructions(fin);
                    }
                }

                objects::Cylinder c;
                c.setMaterial(material);
                c.addTransformation(transform);
                cylinders.push_back(c);
            }
        } else {
            std::cout << "Uknown type: " << type << std::endl;
            fin.close();
            return;
        }
    }
    fin.close();
    
    for (objects::Light& s : lights) { w.addObject(s); }
    for (objects::Sphere& s : spheres) { w.addObject(s); }
    for (objects::Cylinder& s : cylinders) { w.addObject(s); }
    for (objects::Cube& s : cubes) { w.addObject(s); }
    for (objects::Plane& s : planes) { w.addObject(s); }

    auto image = camera.render(w);
    image->save(outputFilename + ".ppm");

    free(image);
}

bool isInstructionsFile(char* filename) {
    size_t i = 0;
    size_t j = 0;
    std::string ext = ".ins";
    while (filename[i]) {
        if (filename[i] == ext[j]) {
            j++;
        } else {
            j = 0;
        }
        if (j == 4) {
            return true;
        }

        i++;
    }

    return false;
}

int main(int argc, char** argv) {
    std::vector<objects::Sphere> spheres;
    std::vector<objects::Cylinder> cylinders;
    std::vector<objects::Plane> planes;
    std::vector<objects::Cube> cubes;
    std::vector<objects::Light> lights;
    if (argc >= 2) {
        if (isInstructionsFile(argv[1])) {
            runInstructionsFile(argv[1]);

            return 0;
        }

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
    } else {
        renderCoverImage();
        
        return 0;
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