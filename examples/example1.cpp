//
// Created by fabian on 02.10.22.
// Usage example for "discreteGaussianKernel".
//

#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <gnuplot-iostream.h>
#include "blobs.hpp"


using namespace boost;
using namespace cv;
using std::filesystem::current_path;


int main(){
    double sigma1 = 5.0;
    double sigma2 = 2.0;
    // Load test image.
    // First, check if file exists.
    ifstream ifile;
    ifile.open("almonds.png");
    Mat test_image;
    test_image = imread( "almonds.png", IMREAD_GRAYSCALE);
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
    return 0;
}


