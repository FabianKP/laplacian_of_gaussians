//
// Created by fabian on 12.08.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "blobDetection.hpp"


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


TEST_CASE("Coordinates of strict local maxima in 3d.", ""){
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
    // Get local maximizers
    vector<CriticalPoint> localMaximizers = strictLocalMaximizer3D(testSSR);
    cout << "Strict local maximums have been found at point:" << endl;
    for(auto point : localMaximizers){
        cout << "(" << point.i << ", " << point.j << ")" << endl;
    }
}