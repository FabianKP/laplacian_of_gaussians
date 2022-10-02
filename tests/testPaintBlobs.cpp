//
// Created by fabian on 27.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "blobDetection.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>


using namespace cv;


TEST_CASE("Test painting blobs in Hubble image.", ""){
    // First, apply LoG to get blobs.
    // Load M54 test image.
    String imageFile = "hubble.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat testImage = imread( imageFile, IMREAD_GRAYSCALE);
    resize(testImage, testImage, Size(), 0.5, 0.5);
    testImage.convertTo(testImage, CV_32FC1);
    normalize(testImage, testImage, 0, 1, NORM_MINMAX);
    // Get scales.
    double sigmaMin {2};
    double sigmaMax {20};
    int numSigma {19};
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(testImage, sigmaMin, sigmaMax, numSigma, 0.02, 0.2);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);
    // Now, call paintBlobs-function.
    Mat imageWithBlobs = paintBlobs(testImage, brightBlobs, BlobList());
    // Visualize results.
    String nameTest = "Original image";
    String nameBlobs = "Image with blobs";
    namedWindow(nameTest, WINDOW_NORMAL);
    namedWindow(nameBlobs, WINDOW_NORMAL);
    imshow(nameTest, testImage);
    imshow(nameBlobs, imageWithBlobs);
    waitKey(0);
    destroyWindow(nameTest);
    destroyWindow(nameBlobs);
}


TEST_CASE("Paint bright blobs of M54 image", ""){
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat testImage = imread( imageFile, IMREAD_GRAYSCALE);
    testImage.convertTo(testImage, CV_32FC1);
    normalize(testImage, testImage, 0, 1, NORM_MINMAX);
    // Upscale image
    resize(testImage, testImage, Size(), 10, 10, INTER_CUBIC);
    // Get sigmas.
    double sigmaMin {1};
    double sigmaMax {50};
    int numSigma {50};
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(testImage, sigmaMin, sigmaMax, numSigma,0.05, 0.5);
    BlobList brightBlobs = get<0>(blobs);
    // Now, call paintBlobs-function.
    Mat imageWithBlobs = paintBlobs(testImage, brightBlobs);
    // Visualize results.
    String nameTest = "Original image";
    String nameBlobs = "Image with blobs";
    namedWindow(nameTest, WINDOW_NORMAL);
    namedWindow(nameBlobs, WINDOW_NORMAL);
    imshow(nameTest, testImage);
    imshow(nameBlobs, imageWithBlobs);
    waitKey(0);
    destroyWindow(nameTest);
    destroyWindow(nameBlobs);
}