//
// Created by fabian on 27.06.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../blobs.h"
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;


TEST_CASE("Scale-space representation of an image", ""){
    /**
     Simple test for the function 'scaleSpaceRepresentation'.
     */
    // Set sigma1 and sigma2 vectors.
    vector<double> sigmaVec = {1., 3., 5., 7., 10};
    int k = sigmaVec.size();
    // Load test image.
    ifstream ifile;
    ifile.open("test_image.png");
    //REQUIRE(ifile);
    Mat test_image = imread( "test_image.png", IMREAD_GRAYSCALE);
    // Compute scale-space representation.
    vector<Mat> ssr = scaleSpaceRepresentation(test_image, sigmaVec, sigmaVec);
    // Check that output is a vector of matrices with the correct scale-length.
    REQUIRE(ssr.size() == k);
    for(int i=0; i < k; i++) {
        String windowName = "Scale-space slice";
        namedWindow(windowName, WINDOW_NORMAL);
        // Get i-th slice of the scale-space representation (i.e. a blurred image)
        Mat ssr_i = ssr[i];
        int sliceRows = ssr_i.rows;
        int sliceCols = ssr_i.cols;
        REQUIRE(sliceRows == test_image.rows);
        REQUIRE(sliceCols == test_image.cols);
        // Show it.
        imshow(windowName, ssr_i);
        waitKey(0);
        destroyWindow(windowName);
    }
}

TEST_CASE("Weighted Laplacian of an image", ""){
    /**
     Simple test for the function 'scaleSpaceRepresentation'.
     */
    // Set sigma1 and sigma2 vectors.
    // Load test image.
    ifstream ifile;
    ifile.open("test_image.png");
    //REQUIRE(ifile);
    Mat testImage = imread( "test_image.png", IMREAD_GRAYSCALE);
    // Compute weighted Laplacian
    double t1 = 2;
    double t2 = 6;
    Mat wl1 = weightedLaplacian(testImage, t1, t2);
    Mat wl2 = weightedLaplacian(testImage, t2, t1);
    // Show images.
    String window1 = "More y";
    String window2 = "More x";
    namedWindow(window1, WINDOW_NORMAL);
    namedWindow(window2, WINDOW_NORMAL);
    imshow(window1, wl1);
    imshow(window2, wl2);
    waitKey(0);
    destroyWindow(window1);
    destroyWindow(window2);
}

TEST_CASE("Scale-normalized Laplacian of an image", ""){
    /**
     Simple test for the function 'scaleSpaceRepresentation'.
     */
    // Set sigma1 and sigma2 vectors.
    vector<double> sigmaVec = {1., 3., 5., 7., 10};
    int k = sigmaVec.size();
    // Load test image.
    ifstream ifile;
    ifile.open("test_image.png");
    //REQUIRE(ifile);
    Mat test_image = imread( "test_image.png", IMREAD_GRAYSCALE);
    // Compute scale-space representation.
    vector<Mat> ssr = scaleSpaceRepresentation(test_image, sigmaVec, sigmaVec);
    // Compute scale-normalized Laplacian of the scale-space representation.
    vector<Mat> snl = scaleNormalizedLaplacian(ssr, sigmaVec, sigmaVec);
    // Check that output is a vector of matrices with the correct scale-length.
    REQUIRE(ssr.size() == k);
    for(int i=0; i < k; i++) {
        String windowName = "Scale-space slice";
        namedWindow(windowName, WINDOW_NORMAL);
        // Get i-th slice of the scale-space representation (i.e. a blurred image)
        Mat snl_i = snl[i];
        int sliceRows = snl_i.rows;
        int sliceCols = snl_i.cols;
        REQUIRE(sliceRows == test_image.rows);
        REQUIRE(sliceCols == test_image.cols);
        // Show it.
        imshow(windowName, snl_i);
        waitKey(0);
        destroyWindow(windowName);
    }
}
