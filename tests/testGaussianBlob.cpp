//
// Created by fabian on 24.06.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../blobs.h"
#include <cstdlib>


TEST_CASE("Test Gaussian blob", ""){
    /**
     * Tests basic functionality of the GaussianBlob class.
     */
     double sigma1 = 2.0;
     double sigma2 = 3.0;
     double x1 = 10.;
     double x2 = 50.;
     double angle = 0.4;
     GaussianBlob gaussianBlob {x1, x2, sigma1, sigma2, angle};
}

