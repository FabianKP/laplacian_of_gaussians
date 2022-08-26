//
// Created by fabian on 17.08.22.
//

#ifndef BLOBS_CPP_STACKTOMATRIX_H
#define BLOBS_CPP_STACKTOMATRIX_H

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "gaussian_filter.h"

using namespace cv;
using namespace std;


Mat stackToMatrix(const vector<Mat>& stack){
    /**
     * Converts a stack of two-dimensional matrices into a 3-dimensional matrix.
     */
     // First, check that dimensions match.
     int k = stack.size();
     int m0 = stack[0].rows;
     int n0 = stack[0].cols;
     auto type0 = stack[0].type();
     for (const auto& slice : stack){
         assert(slice.dims == 2 && slice.rows == m0 && slice.cols == n0 && slice.type() == type0);
     }
     // Initialize 3d-matrix.
     int sizes[] = {k, m0, n0};
     Mat stackedMatrix(3, sizes, stack[0].type());
     // Fill it slice-by-slice.
     for (int i=0; i<k; i++){
         Range sliceIndices[3] = {Range(i, i+1), Range::all(), Range::all()};
         stackedMatrix(sliceIndices) = stack[i];
     }
    return stackedMatrix;
}


vector<Mat> matrixToStack(const Mat& input){
    /**
     * Opposite of stackToMatrix
     */
    // First, check that dimensions match.
    assert(input.dims == 3);
    // Get first dimension of matrix.
    int k = input.size[0];
    int m = input.size[1];
    int n = input.size[2];
    // Initialize vector of matrices.
    vector<Mat> stack;
    // Fill it slice-by-slice.
    for (int i=0; i < k; i++){
        Range ranges[3] = {Range(i, i+1), Range::all(), Range::all()};
        Mat slice_i(m, n, input.type(), input(ranges).data);
        stack.push_back(slice_i);
    }
    // Check that stack consists of 2D matrices.
    for (const auto& mat : stack){
        assert(mat.dims == 2);
    }
    return stack;
}


#endif //BLOBS_CPP_STACKTOMATRIX_H
