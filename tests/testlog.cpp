//
// Created by fabian on 12.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "blobDetection.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;


TEST_CASE("LoG applied to M54 galaxy", ""){
    // Load M54 test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // Set scale interval.
    double sigmaMin {1};
    double sigmaMax {15};
    int numSteps {15};
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(test_image, sigmaMin, sigmaMax, numSteps, 0.1,0.5);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);

    cout << "LoG detected " << brightBlobs.size() << " bright blobs and " << darkBlobs.size() << " dark blobs";
}


TEST_CASE("LoG applied to apple image", ""){
    // Load M54 test image.
    String imageFile = "apples.png";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // Set scale interval.
    double sigmaMin {1};
    double sigmaMax {100};
    int numSigma {20};
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(test_image, sigmaMin, sigmaMax, numSigma, 0.1, 0.5);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);

    cout << "LoG detected " << brightBlobs.size() << " bright blobs and " << darkBlobs.size() << " dark blobs";
}


TEST_CASE("Calling LoG with a color image raises a runtime error.", ""){
    String imageFile = "test_image.png";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_COLOR);
    // Get scales.
    double sigmaMin {1};
    double sigmaMax {100};
    int numSigma {20};
    // Apply LoG.
    REQUIRE_THROWS_AS(LoG(test_image, sigmaMin, sigmaMax, numSigma, 0.1, 0.5), runtime_error);
}
