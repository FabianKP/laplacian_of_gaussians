//
// Created by fabian on 19.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <opencv2/opencv.hpp>
#include "blobDetection.hpp"


using namespace std;
using namespace cv;


TEST_CASE("Mat-stack to 3d vector", ""){
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // In front and after, stack the same image, but of half intensity.
    vector<Mat> test_stack;
    test_stack.push_back(0.5 * test_image);
    test_stack.push_back(test_image);
    test_stack.push_back(0.5 * test_image);
    vector<vector<vector<float>>> array = matToArray3D(test_stack);
    for (auto mat : array){
        for (auto row : mat){
            for (auto val : row){
                cout << int(val);
            }
            cout << endl;
        }
        cout << endl;
        cout << "-----------------" << endl;
    }
}


TEST_CASE("Finding strict local maximizers", ""){
    // Create a test array in 3d by taking an image and appending copies of reduced intensity.
    // In that case, the 2d-local maximizer should also be 3d-local maximizers.
    // So, load the test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // In front and after, stack the same image, but of half intensity.
    vector<Mat> test_stack;
    test_stack.push_back(0.5 * test_image);
    test_stack.push_back(test_image);
    test_stack.push_back(0.5 * test_image);
    // Get strict local maximizers.
    vector<CriticalPoint> localMaximizers = strictLocalMaximizer3D(test_stack);
    // Visualize by creating an image where the local maximizers are marked.
    for (auto pt: localMaximizers){
        test_image.at<float>(pt.i, pt.j) = 1.;
    }
    // Show the image.
    String imageName = "Local maximizers";
    namedWindow(imageName, WINDOW_NORMAL);
    imshow(imageName, test_image);
    waitKey(0);
    destroyWindow(imageName);
}

TEST_CASE("Finding strict local minimizers", ""){
    // Create a test array in 3d by taking an image and appending copies of reduced intensity.
    // In that case, the 2d-local maximizer should also be 3d-local maximizers.
    // So, load the test image.
    String imageFile = "m54.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    REQUIRE(ifile);
    Mat test_image = imread( imageFile, IMREAD_GRAYSCALE);
    test_image.convertTo(test_image, CV_32FC1);
    normalize(test_image, test_image, 0, 1, NORM_MINMAX);
    // In front and after, stack the same image, but of half intensity.
    vector<Mat> test_stack;
    test_stack.push_back(2. * test_image);
    test_stack.push_back(test_image);
    test_stack.push_back(2. * test_image);
    // Get strict local maximizers.
    vector<CriticalPoint> localMinimizers = strictLocalMinimizer3D(test_stack);
    // Visualize by creating an image where the local maximizers are marked.
    for (auto pt: localMinimizers){
        test_image.at<float>(pt.i, pt.j) = 1.;
    }
    // Show the image.
    String imageName = "Local minimizers";
    namedWindow(imageName, WINDOW_NORMAL);
    imshow(imageName, test_image);
    waitKey(0);
    destroyWindow(imageName);
}