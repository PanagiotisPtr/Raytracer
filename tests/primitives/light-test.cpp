#include "gtest/gtest.h"
#include "math/utility.h"

#include <cstddef>

#include "objects/light.h"
#include "drawing/colour.h"
#include "primitives/constants.h"

TEST(lightTests, constructorBaseCase) {
    drawing::Colour colour = {1,1,1};
    primitives::Point3D origin = {0,0,0,1};
    objects::Light light(colour, origin);

    EXPECT_EQ(colour.green(), light.getIntensity().green());
    EXPECT_EQ(colour.red(), light.getIntensity().red());
    EXPECT_EQ(colour.blue(), light.getIntensity().blue());

    EXPECT_EQ(origin, light.getOrigin());
}
