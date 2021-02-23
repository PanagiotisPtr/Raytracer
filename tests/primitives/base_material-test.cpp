#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>

#include "primitives/constants.h"
#include "primitives/material.h"
#include "primitives/base_material.h"
#include "drawing/colour.h"

TEST(baseMaterialTests, constructorBaseCase) {
    drawing::Colour colour = {1,1,1};
    primitives::PrecisionType ambient = 0.55;
    primitives::PrecisionType diffuse = 1.1;
    primitives::PrecisionType specular = 0.8;
    primitives::PrecisionType shininess = 100;
    primitives::PrecisionType reflectivity = 0.5;
    primitives::BaseMaterial m(
        colour,
        ambient,
        diffuse,
        specular,
        shininess,
        reflectivity
    );

    EXPECT_EQ(colour.green(), m.colour.green());
    EXPECT_EQ(colour.red(), m.colour.red());
    EXPECT_EQ(colour.blue(), m.colour.blue());

    EXPECT_EQ(ambient, m.ambient);
    EXPECT_EQ(diffuse, m.diffuse);
    EXPECT_EQ(specular, m.specular);
    EXPECT_EQ(shininess, m.shininess);
    EXPECT_EQ(reflectivity, m.reflective);
}

TEST(baseMaterialTests, defaultValuesConstructorTest) {
    primitives::BaseMaterial defaultMaterial;
    drawing::Colour defaultColour = {1,1,1};

    EXPECT_EQ(defaultColour.green(), defaultMaterial.colour.green());
    EXPECT_EQ(defaultColour.red(), defaultMaterial.colour.red());
    EXPECT_EQ(defaultColour.blue(), defaultMaterial.colour.blue());

    EXPECT_EQ(0.1, defaultMaterial.ambient);
    EXPECT_EQ(0.9, defaultMaterial.diffuse);
    EXPECT_EQ(0.9, defaultMaterial.specular);
    EXPECT_EQ(200.0, defaultMaterial.shininess);
    EXPECT_EQ(0.0, defaultMaterial.reflective);
}