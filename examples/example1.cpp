//
// Created by fabian on 02.10.22.
// Usage example for "gaussianFilter2D".
//

// First, include some stuff for file-handling.
#include <fstream>
#include <filesystem>
#include <gnuplot-iostream.h>
// We also need to include OpenCV.
#include <opencv2/opencv.hpp>
// Include blobs-files.
#include "blobDetection.hpp"


using namespace cv;
using std::filesystem::current_path;


int main(){
    // We test the Gaussian filter on a test image of almonds.
    String testImageName = "almonds.png";
    // First, we check that the file exists.
    ifstream ifile;
    ifile.open(testImageName);
    // Next, we load the image into an OpenCV matrix.
    Mat test_image;
    test_image = imread( testImageName, IMREAD_GRAYSCALE);
    // The Gaussian filter has two parameters corresponding to the standard deviation of the Gaussian kernel in x1-
    // and x2-direction (horizontal and vertical).
    double sigma1 = 5.0;
    double sigma2 = 2.0;
    // We apply the filter by calling the `gaussianFilter2d`-function.
    Mat blurred_image = gaussianFilter2d(test_image, sigma1, sigma2);
    // Finally, we plot both images with OpenCV.
    String nameTest = "Original image";
    String nameBlurred = "Filtered image with sigma1 = " + to_string(sigma1) + " and sigma2 = "
                         + to_string(sigma2);
    namedWindow(nameTest, WINDOW_NORMAL);
    namedWindow(nameBlurred, WINDOW_NORMAL);
    imshow(nameTest, test_image);
    imshow(nameBlurred, blurred_image);
    // Press enter to close the windows.
    waitKey(0);
    destroyWindow(nameTest);
    destroyWindow(nameBlurred);
    // Store the image.
    imwrite("blurred_almonds.jpg", blurred_image);
    return 0;
}


