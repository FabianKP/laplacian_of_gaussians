//
// Created by fabian on 12.08.22.
//

#ifndef BLOBS_CPP_LOCALMINMAX_H
#define BLOBS_CPP_LOCALMINMAX_H

#include "stackToMatrix.h"

using namespace std;
using namespace cv;


void strictLocalMax2d(const Mat& input, Mat& output){
    /**
     * Returns image where strict local maxima are 1 and everything else is 0.
     */
    // First, we get an image where every point is replaced with the maximum in its neighbourhood, excluding itself.
    Mat wholeInMiddle = (Mat_<int>(3, 3) <<
                                         1, 1, 1,
            1, 0, 1,
            1, 1, 1);
    wholeInMiddle.convertTo(wholeInMiddle, CV_8U);
    dilate(input, output, wholeInMiddle);
    // Then, compare against localMaxImage. Set pixel to 1 only if larger than dilated image.
    compare(input, output, output, CMP_GT);
}


void strictLocalMin2d(const Mat& input, Mat& output){
    strictLocalMax2d(255 - input, output);
}


vector<Point> strictLocalMax2d(const Mat& input){
    /**
     * Returns coordinates of strict local maxima as Point objects.
     */
     // First, get image of strict local maxima.
     Mat localMaxImage;
    strictLocalMax2d(input, localMaxImage);
    // Extract coordinates of all pixels > 0.
    vector<Point> localMaxLocations;
    findNonZero(localMaxImage, localMaxLocations);
    return localMaxLocations;
}


vector<Point> strictLocalMin2d(const Mat& input){
    return strictLocalMax2d(255 - input);
}


void strictLocalMax3d(const Mat& input, Mat& output){
    /**
     * Returns 3-dimensional array where local maxima are set to 1, rest 0.
     */
     // Check that input is a 3-dimensional grayscale matrix.
     assert(input.dims == 3);
     assert(input.channels() == 1);
     // Create 3-dimensional kernel.
     int sizes[] = {3, 3, 3};
     Mat wholeInMiddle = Mat::ones(3, sizes, CV_8U);
     wholeInMiddle.at<uchar>(1, 1, 1) = 0;
     dilate(input, output, wholeInMiddle);
     // Then, compare against localMaxImage. Set pixel to 1 only if larger than dilated image.
     compare(input, output, output, CMP_GT);
}


vector<Point> findNonZero3d(Mat& input){
    vector<Mat> stack = matrixToStack(input);
    assert(input.dims == 3);
    vector<Point3d> nonzeros3d;
    for (int i=0; i<stack.size(); i++){
        // Find nonzeros in the i-th slice.
        vector<Point> nonzeros2d;
        findNonZero(stack[i], nonzeros2d);
        // nonzero (y, x) -> nonzero (i, y, x) in 3d-array.
        for (auto point2d : nonzeros2d){
            nonzeros3d.emplace_back(i, point2d.y, point2d.x);
        }
    }
}


vector<Point> strictLocalMax3d(const Mat& input){
    /**
     * Returns coordinates of strict local maxima as Point objects.
     */
    // First, get image of strict local maxima.
    Mat localMaxImage;
    strictLocalMax3d(input, localMaxImage);
    // Extract coordinates of all pixels > 0.
    // Since findNonZero is only implemented for 2d matrices in opencv, we have to use a custom implementation.
    vector<Point> localMaxLocations = findNonZero3d(localMaxImage);
    return localMaxLocations;
}


#endif //BLOBS_CPP_LOCALMINMAX_H


