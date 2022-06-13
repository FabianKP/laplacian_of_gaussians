//
// Created by fabian on 11.06.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../blobs.h"
#include <cstdlib>
#include <boost/math/distributions/normal.hpp>

#include <gnuplot-iostream.h>


using namespace boost;


TEST_CASE( "Discrete Gaussian kernel", ""){
    /**
     * Test for discreteGaussianKernel
     */
    double sigma = 3.0;
    vector<double> kernel = discreteGaussianKernel(sigma);
    int size = kernel.size();
    int required_radius = 4 * ((int)sigma + 1);
    int required_size = 2 * required_radius + 1;

    // For comparison, create standard Gaussian kernel.
    vector<double> indices(size);
    std::iota(indices.begin(), indices.end(), -required_radius);
    boost::math::normal nd(0.0, sigma);
    vector<double> gaussian(size);
    for (int i=0; i<size; i++){
        gaussian[i] = boost::math::pdf(nd, indices[i]);
    }
    // Plot with gnuplot.
    Gnuplot gp("gnuplot -persist"); // persist makes the window survive the programs exit
    gp << "set title 'Kernel'\n";
    gp << "plot '-' with lines title 'discrete Gaussian',"
        << "'-' with lines title 'sampled Gaussian'\n";
    gp.send(kernel);
    gp.send(gaussian);

    REQUIRE(size == required_size);
}


TEST_CASE("Gaussian filter 2d", ""){
    /**
     * Test for gaussianFilter2d.
     */
    // Load test image.
    // Convolve test image.
    // Show both images using OpenCV.

}



