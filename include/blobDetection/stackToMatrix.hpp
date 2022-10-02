//
// Created by fabian on 17.08.22.
//

#ifndef BLOBS_CPP_STACKTOMATRIX_HPP
#define BLOBS_CPP_STACKTOMATRIX_HPP

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "gaussian_filter.hpp"

using namespace cv;
using namespace std;


/**
 * Opposite of stackToMatrix. Converts a 3-dimensional cv::Mat into a vector of 2-dimensional cv::Mat-objects.
 *
 * @param input Must be a 3-dimensional cv::Mat-object.
 * @return A vector of matrices obtained by slicing the input along the first axis.
 */
vector<Mat> matrixToStack(const Mat& input){
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


#endif //BLOBS_CPP_STACKTOMATRIX_HPP
