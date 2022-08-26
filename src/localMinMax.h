//
// Created by fabian on 12.08.22.
//

#ifndef BLOBS_CPP_LOCALMINMAX_H
#define BLOBS_CPP_LOCALMINMAX_H

#include "stackToMatrix.h"
#include "strictLocalMaximizer3D.h"

using namespace std;
using namespace cv;


void strictLocalMax2D(const Mat& input, Mat& output){
    /**
     * Returns image where strict local maxima are 1 and everything else is 0.
     */
    // First, we get an image where every point is replaced with the maximum in its neighbourhood, excluding itself.
    Mat wholeInMiddle = Mat::ones(3, 3, CV_8U);
    wholeInMiddle.at<uchar>(1, 1) = 0;
    //wholeInMiddle.convertTo(wholeInMiddle, CV_8U);
    dilate(input, output, wholeInMiddle);
    // Then, compare against localMaxImage. Set pixel to 1 only if larger than dilated image.
    compare(input, output, output, CMP_GT);
}


void justDilate3d(const Mat& input, Mat& output){
    assert(input.dims == 3);
    assert(input.channels() == 1);
    // Create 3-dimensional kernel.
    int sizes[] = {3, 3, 3};
    Mat wholeInMiddle = Mat::ones(3, sizes, CV_8U);
    wholeInMiddle.at<uchar>(1, 1, 1) = 0;
    dilate(input, output, wholeInMiddle, Point(-1, -1), 1, BORDER_REFLECT_101);
}


vector<Point> strictLocalMaximizers2D(const Mat& input){
    /**
     * Returns coordinates of strict local maxima as Point objects.
     */
     // First, get image of strict local maxima.
     Mat localMaxImage;
    strictLocalMax2D(input, localMaxImage);
    // Extract coordinates of all pixels > 0.
    vector<Point> localMaxLocations;
    findNonZero(localMaxImage, localMaxLocations);
    return localMaxLocations;
}


vector<Point> strictLocalMinimizers2D(const Mat& input){
    return strictLocalMaximizers2D(255 - input);
}


#endif //BLOBS_CPP_LOCALMINMAX_H


