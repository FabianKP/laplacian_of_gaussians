//
// Created by fabian on 11.06.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "blobDetection.hpp"
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <boost/math/distributions/normal.hpp>
#include <opencv2/opencv.hpp>

#include <gnuplot-iostream.h>


using namespace boost;
using namespace cv;
using namespace std;
using std::filesystem::current_path;


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
    gp.send(gaussian);
    gp.send(kernel);

    REQUIRE(size == required_size);
}


TEST_CASE("Gaussian filter 2d", ""){
    /**
     * Test for gaussianFilter2d.
     */
    // Set parameters.
    double sigma1 = 5.0;
    double sigma2 = 1.0;
    // Load test image.
    // First, check if file exists.
    ifstream ifile;
    ifile.open("test_image.png");
    REQUIRE(ifile);
    Mat test_image;
    test_image = imread( "test_image.png", IMREAD_GRAYSCALE);
    REQUIRE(!test_image.empty());
    // Convert to gray scale.
    //cv::cvtColor(test_image, test_image, COLOR_BGR2GRAY);
    // Convolve test image.
    Mat blurred_image = gaussianFilter2d(test_image, sigma1, sigma2);
    // Show both images using OpenCV.
    String nameTest = "Original image";
    String nameBlurred = "Filtered image with sigma1 = " + to_string(sigma1) + " and sigma2 = "
            + to_string(sigma2);
    namedWindow(nameTest, WINDOW_NORMAL);
    namedWindow(nameBlurred, WINDOW_NORMAL);
    imshow(nameTest, test_image);
    imshow(nameBlurred, blurred_image);
    waitKey(0);
    destroyWindow(nameTest);
    destroyWindow(nameBlurred);
}


TEST_CASE("Filter with sigma similar to image size", ""){
    /**
     * Test for gaussianFilter2d.
     */
    // Set parameters.
    // Load test image.
    // First, check if file exists.
    ifstream ifile;
    String location = "apples.png";
    ifile.open(location);
    REQUIRE(ifile);
    Mat test_image;
    test_image = imread( location, IMREAD_GRAYSCALE);
    REQUIRE(!test_image.empty());
    // Convert to gray scale.
    //cv::cvtColor(test_image, test_image, COLOR_BGR2GRAY);
    // Convolve test image.
    double sigma = 40;
    Mat blurred_image = gaussianFilter2d(test_image, sigma, sigma);
    // Show both images using OpenCV.
    String nameTest = "Original image";
    String nameBlurred = "Filtered image with sigma = " + to_string(sigma);
    namedWindow(nameTest, WINDOW_NORMAL);
    namedWindow(nameBlurred, WINDOW_NORMAL);
    imshow(nameTest, test_image);
    imshow(nameBlurred, blurred_image);
    waitKey(0);
    destroyWindow(nameTest);
    destroyWindow(nameBlurred);
}



