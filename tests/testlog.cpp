//
// Created by fabian on 12.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../blobs.h"
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
    // Get scales.
    vector<double> sigmas {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(test_image, sigmas, 0.1, 0.5);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);

    cout << "LoG detected " << brightBlobs.size() << " bright blobs and " << darkBlobs.size() << " dark blobs";
}


TEST_CASE("LoG applied to almonds image", ""){
    // Load M54 test image.
    String imageFile = "test_image.png";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // Get scales.
    vector<double> sigmas;
    for (int i=1; i<20; i++){
        sigmas.push_back(5 * i);
    }
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(test_image, sigmas, 0.1, 0.5);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);

    cout << "LoG detected " << brightBlobs.size() << " bright blobs and " << darkBlobs.size() << " dark blobs";
}
