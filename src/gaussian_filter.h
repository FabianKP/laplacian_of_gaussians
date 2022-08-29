//
// Created by fabian on 01.08.22.
//

#ifndef BLOBS_CPP_GAUSSIAN_FILTER_H
#define BLOBS_CPP_GAUSSIAN_FILTER_H

#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


/**
 * Returns the one-dimensional normalized kernel for the discrete analog of the Gaussian.
 * T(i, t) = exp(-sigma^2) * sum_{k=0}^infty 1 / (k!(m+k)!) * (t/2)^(2m + k).
 *
 * @param sigma The deviation of the kernel.
 * @param truncation The truncation radius of the kernel. The kernel is truncated to have a radius of
 *  truncation * sigma.
 * @return A vector of size 2 * ceil(truncation + 1).
 */
vector<double> discreteGaussianKernel(double sigma, double truncation=4.0){
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


/**
 * Filters a given matrix with a discrete Gaussian filter.
 *
 * @param image The input array.
 * @param sigma1 The standard deviation in vertical direction.
 * @param sigma2 The standard deviation in horizontal direction.
 * @param truncation The filter kernel is truncated at radius = truncation * sigma. Defaults to 4.
 * @return The filtered image.
 */
Mat gaussianFilter2d(const Mat& image, double sigma1, double sigma2, double truncation=4.0){
    // Input must be a 2D image.
    int idims = image.dims;
    if (idims != 2){
        cerr << "Error: Atm, this program only supports twodimensional images." << endl;
    }
    // The standard deviations should be strictly positive.
    if (sigma1 <= 0.){
        cerr << "Error: sigma1 must be nonnegative." << endl;
    }
    if (sigma2 <= 0.){
        cerr << "Error: sigma1 must be nonnegative." << endl;
    }
    // Same for truncation number.
    if (truncation <= 0.){
        cerr << "Error: truncation must be a strictly positive number" << endl;
    }
    // Get the Bessel kernels corresponding to sigma1 and sigma 2.
    vector<double> kernel1 = discreteGaussianKernel(sigma1, truncation);
    vector<double> kernel2 = discreteGaussianKernel(sigma2, truncation);
    // Perform the separable convolution.
    Mat output;
    sepFilter2D(image, output, -1, kernel1, kernel2);
    return output;
}


#endif //BLOBS_CPP_GAUSSIAN_FILTER_H
