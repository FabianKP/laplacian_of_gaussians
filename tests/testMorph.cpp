//
// Created by fabian on 12.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "../blobs.h"


using namespace cv;
using namespace std;


TEST_CASE("Test dilate", ""){
    // Get test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    int size = 1;
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    // Dilate with 3x3-matrix as structuring element.
    Mat kernel = getStructuringElement( MORPH_RECT, Size( 2 * size + 1, 2 * size +1 ),
                                        Point(1,1 ) );
    Mat output;
    dilate(test_image, output, Mat());
    Mat comparison;
    compare(test_image, output, comparison, CMP_GE);
    // Show dilated image.
    String original = "Original image";
    String dilated = "Dilated image";
    String equal = "Comparison";
    namedWindow(original, WINDOW_NORMAL);
    namedWindow(dilated, WINDOW_NORMAL);
    namedWindow(equal, WINDOW_NORMAL);
    imshow(original, test_image);
    imshow(dilated, output);
    imshow(equal, comparison);
    waitKey(0);
    destroyWindow(original);
    destroyWindow(dilated);
    destroyWindow(equal);
}


TEST_CASE("Strict local max", ""){
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    int size = 1;
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    // Then, compare against localMaxImage. Set pixel to 1 only if larger than punctuatedImage.
    Mat localMaxima;
    strictLocalMax2d(test_image, localMaxima);
    // Show dilated image.
    String originalName = "Original image";
    String localMaximaName = "Comparison";
    namedWindow(originalName, WINDOW_NORMAL);
    namedWindow(localMaximaName, WINDOW_NORMAL);
    imshow(originalName, test_image);
    imshow(localMaximaName, localMaxima);
    waitKey(0);
    destroyWindow(originalName);
    destroyWindow(localMaximaName);
}


TEST_CASE("Get coordinates of strict local maxima", ""){
    // Get test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_8U);
    // Get coordinates of local maximizers.
    vector<Point> localMaximizers = strictLocalMax2d(test_image);
    // Create image where local maximizers are set to 1 rest 0.
    Mat localMaxima = Mat::zeros(test_image.rows, test_image.cols, CV_8U);
    for (auto point : localMaximizers){
        localMaxima.at<uchar>(point) = 255;
    }
    // Show original image and local maxima.
    String originalName = "Original image";
    String localMaximaName = "Comparison";
    namedWindow(originalName, WINDOW_NORMAL);
    namedWindow(localMaximaName, WINDOW_NORMAL);
    imshow(originalName, test_image);
    imshow(localMaximaName, localMaxima);
    waitKey(0);
    destroyWindow(originalName);
    destroyWindow(localMaximaName);
}


TEST_CASE("Image of strict local maxima in 3d", ""){
    // Get test image.
    // Get test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_8U);
    // Since we need a 3-dimensional object for the test, compute a scale-space representation.
    vector<double> sigmaVec = {1., 3., 5., 7., 10};
    vector<Mat> testSSR = scaleSpaceRepresentation(test_image, sigmaVec, sigmaVec);
    // convert vector of 2d-matrices to 3d-matrix.
    Mat testMat = stackToMatrix(testSSR);
    // Get local maxima.
    Mat localMaxima;
    strictLocalMax3d(testMat, localMaxima);
    // Check that output has matching dimensions.
    REQUIRE(localMaxima.dims == testMat.dims);
    REQUIRE(localMaxima.size == testMat.size);
}


TEST_CASE("Coordinates of strict local maxima in 3d", ""){
    // Get test image.
    // Get test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_8U);
    // Since we need a 3-dimensional object for the test, compute a scale-space representation.
    vector<double> sigmaVec = {1., 3., 5., 7., 10};
    vector<Mat> testSSR = scaleSpaceRepresentation(test_image, sigmaVec, sigmaVec);
    // convert vector of 2d-matrices to 3d-matrix.
    Mat testMat = stackToMatrix(testSSR);
    // Get local maximizers
    vector<Point> localMaximizers = strictLocalMax3d(testMat);
    cout << "Strict local maximums have been found at point:" << endl;
    for(auto point : localMaximizers){
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}