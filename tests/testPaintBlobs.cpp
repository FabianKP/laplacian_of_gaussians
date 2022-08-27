//
// Created by fabian on 27.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../blobs.h"
#include <cstdlib>
#include <opencv2/opencv.hpp>


using namespace cv;


TEST_CASE("Test painting blobs in almond image", ""){
    // First, apply LoG to get blobs.
    // Load M54 test image.
    String imageFile = "test_image.png";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile);
    test_image.convertTo(test_image, CV_32FC1);
    Mat neg_image = -test_image;
    cvtColor(neg_image, neg_image, COLOR_BGR2GRAY);
    normalize(neg_image, neg_image, 0, 1, NORM_MINMAX);
    // Get scales.
    vector<double> sigmas;
    for (int i=1; i<20; i++){
        sigmas.push_back(10 * i);
    }
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(neg_image, sigmas, 0.1, 0.5);
    // Now, call paintBlobs-function.
    paintBlobs(test_image, blobs);
}


TEST_CASE("Paint blobs of M54 image", ""){
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile);
    test_image.convertTo(test_image, CV_32FC1);
    // Upscale image
    resize(test_image, test_image, Size(), 10, 10);
    Mat neg_image = test_image;
    cvtColor(neg_image, neg_image, COLOR_BGR2GRAY);
    normalize(neg_image, neg_image, 0, 1, NORM_MINMAX);
    // Get scales.
    vector<double> sigmas;
    for (int i=1; i<15; i++){
        sigmas.push_back(10 * i);
    }
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(neg_image, sigmas, 0.1, 0.5);
    // Now, call paintBlobs-function.
    paintBlobs(test_image, blobs);
}