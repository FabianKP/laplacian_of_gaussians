//
// Created by fabian on 11.06.22.
//

#ifndef BLOBS_CPP_GAUSSIAN_FILTER_H
#define BLOBS_CPP_GAUSSIAN_FILTER_H

#include <cstdlib>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


vector<double> discreteGaussianKernel(double sigma, double truncation=4.0){
    /**
     @brief Returns the one-dimensional normalized kernel for the discrete analog of the Gaussian.
     T(i, t) = exp(-sigma^2) * sum_{k=0}^infty 1 / (k!(m+k)!) * (t/2)^(2m + k).
     @param[sigma] The deviation of the kernel.
     @param[truncation] The truncation radius of the kernel.
     @return A vector of dimension 2 * truncation + 1.
     */
     int sigmaCeil = (int)sigma + 1;
     int kernel_radius = (int)truncation * sigmaCeil;
     int kernel_size = 2 * kernel_radius + 1;
     double t = sigma * sigma;
     vector<double> kernel(kernel_size);
     // Fill kernel with Bessel values.
     for (int i=-kernel_radius; i <= kernel_radius; i++){
         uint i_abs = abs(i);
         kernel[kernel_radius + i] = exp(-t) * cyl_bessel_i(double(i_abs), t);
     }
     return kernel;
}


void gaussianFilter1d(InputArray& input, OutputArray& output, double sigma, double truncation){
    /**
     @brief Implements a 1-dimensional Gaussian filter.
     @param[input]  The input array.
     @param[output] The array in which to write the result of the filter.ge.
     @param[sigma] The standard deviation of the discrete Gaussian kernel.
     @param[truncation] The filter kernel is truncated at radius truncation * sigma. Defaults to 4.
     @return void.
     */
}


void gaussianFilter2d(InputArray& input, OutputArray & output, double sigma1, double sigma2, double truncation){
    /**
     @brief Implements a 1-dimensional Gaussian filter.
     @param[input]  The input array.
     @param[output] The array in which to write the result of the filter.ge.
     @param[sigma1] The standard deviation in vertical direction.
     @param[sigma2] The standard deviation in horizontal direction.
     @param[truncation] The filter kernel is truncated at radius truncation * sigma. Defaults to 4.
     @return void.
     */
}


#endif //BLOBS_CPP_GAUSSIAN_FILTER_H
