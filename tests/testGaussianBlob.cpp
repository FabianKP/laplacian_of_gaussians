//
// Created by fabian on 24.06.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdlib>
#include "blobDetection.hpp"


TEST_CASE("Test Gaussian blob.", ""){
    /**
     * Tests basic functionality of the GaussianBlob class.
     */
     double sigma1 = 2.0;
     int x1 = 10.;
     int x2 = 50.;
     float strength = 0.4;
     GaussianBlob gaussianBlob {x1, x2, sigma1, strength};
}

