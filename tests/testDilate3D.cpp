//
// Created by fabian on 18.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/blobs.hpp"


TEST_CASE("OpenCV-dilate 3D", ""){
    /**
     * Test whether OpenCV's dilate-implementation works with 3D-matrices.
     */
    // Load test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    int size = 1;
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    // Create stack of copies.
    int nStack = 10;
    vector<Mat> testStack;
    for (int i=0; i<nStack; i++) {
        testStack.push_back(test_image.clone());
    }
    Mat test3D = stackToMatrix(testStack);
    // Dilate the test image.
    Mat dilated2D;
    dilate(test_image, dilated2D, Mat(), Point(-1, -1), 1, BORDER_REFLECT_101);
    // Dilate the stack.
    Mat dilated3D;
    justDilate3d(test3D, dilated3D);
    Range ranges[3] = {Range(1, 2), Range::all(), Range::all()};
    int m = test_image.rows;
    int n = test_image.cols;
    Mat sliceOfDilated3D(m, n, dilated3D.type(), dilated3D(ranges).data);
    // Results should look the same.
    String nameForImage = "Original image";
    String nameFor2D = "Dilated in 2D";
    String nameFor3DSlice = "Dilated in 3D";
    namedWindow(nameForImage, WINDOW_NORMAL);
    namedWindow(nameFor2D, WINDOW_NORMAL);
    namedWindow(nameFor3DSlice, WINDOW_NORMAL);
    imshow(nameForImage, test_image);
    imshow(nameFor2D, dilated2D);
    imshow(nameFor3DSlice, sliceOfDilated3D);
    waitKey(0);
    destroyWindow(nameForImage);
    destroyWindow(nameFor2D);
    destroyWindow(nameFor3DSlice);
    // So, I guess I have to implement dilation myself!!!
}