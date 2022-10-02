//
// Created by fabian on 26.08.22.
//

#define CATCH_CONFIG_MAIN
#include <cmath>
#include "catch.hpp"
#include "../src/blobs.hpp"


using namespace std;


TEST_CASE("Compute relative overlap of non-intersecting blobs", ""){
    // Create two blobs that do not intersect.
    int i1 = 0;
    int j1 = 0;
    double r1 = 3.9;
    double sigma1 = r1 / sqrt(2);
    int i2 = 4;
    int j2 = 3;
    double r2 = 1;
    double sigma2 = r2 / sqrt(2);
    GaussianBlob largerBlob(i1, j1, sigma1, 0.);
    GaussianBlob smallerBlob(i2, j2, sigma2, 0.);
    // Check that they truly do not intersect.
    double distance = sqrt((i1-i2)*(i1-i2) + (j1-j2)*(j1-j2));
    REQUIRE(distance > r1 + r2);
    // Hence, the computed overlap should be EXACTLY 0.
    double relativeOverlap = computeRelativeOverlap(largerBlob, smallerBlob);
    REQUIRE(relativeOverlap == 0.);
}


TEST_CASE("Compute relative overlap when one blob is inside the other one."){
    int i1 = 0;
    int j1 = 0;
    double r1 = 4;
    double sigma1 = r1 / sqrt(2);
    int i2 = 1;
    int j2 = 1;
    double r2 = 1;
    double sigma2 = r2 / sqrt(2);
    GaussianBlob largerBlob(i1, j1, sigma1, 0.);
    GaussianBlob smallerBlob(i2, j2, sigma2, 0.);
    // Check that distance < r1 - r2, which means that the larger blob contains the smaller one.
    double distance = sqrt((i1-i2)*(i1-i2) + (j1-j2)*(j1-j2));
    REQUIRE(distance < r1 - r2);
    // Hence, the computed overlap should be EXACTLY 1.
    double relativeOverlap = computeRelativeOverlap(largerBlob, smallerBlob);
    REQUIRE(relativeOverlap == 1);
}


TEST_CASE("Compute relative overlap of intersecting blobs", ""){
    int i1 = 0;
    int j1 = 0;
    double r1 = 20;
    double sigma1 = r1 / sqrt(2);
    int i2 = 1;
    int j2 =1;
    double r2 = 20;
    double sigma2 = r2 / sqrt(2);
    GaussianBlob largerBlob(i1, j1, sigma1, 0.);
    GaussianBlob smallerBlob(i2, j2, sigma2, 0.);
    // Check that distance < r1 + r2, which means that the blobs intersect.
    double distance = sqrt((i1-i2)*(i1-i2) + (j1-j2)*(j1-j2));
    REQUIRE(distance < r1 + r2);
    // Hence, the computed relative overlap should in (0, 1).
    double relativeOverlap = computeRelativeOverlap(largerBlob, smallerBlob);
    REQUIRE(relativeOverlap > 0);
    REQUIRE(relativeOverlap < 1);
}
