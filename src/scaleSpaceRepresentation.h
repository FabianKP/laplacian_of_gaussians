//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_SCALESPACEREPRESENTATION_H
#define BLOBS_CPP_SCALESPACEREPRESENTATION_H

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "gaussian_filter.h"


using namespace cv;
using namespace std;


vector<Mat> scaleSpaceRepresentation(const Mat& image, const vector<double>& sigma1, const vector<double>& sigma2){
    /**
     @brief Given an image and a list of scales, creates the Gaussian scale-space representation.
     @param[image] The input image. Must be 2-dimensional and grayscale.
     @param[sigma1] The list of vertical standard deviations.
     @param[sigma2] The list of horizontal standard deviations.
     @return Returns the 3-dimensional scale-space representation.
     */
     // Check input for consistency. The image must be 2-dimensional and grayscale.
     assert(image.dims == 2 && image.channels() == 1);
     // sigma1 and sigma2 must have the same length.
    assert(sigma1.size() == sigma2.size());
    int k = sigma1.size();
    int n1 = image.rows;
    int n2 = image.cols;
    int ssrShape[3] = {k, n1, n2};
    // Initialize scale-space representation as vector of matrices.
    vector<Mat> ssr(k);
     // Compute scale-space representation by filtering the image multiple times.
     // The results are written into 'ssr' in a plane-by-plane fashion.
     for (int i=0; i<k; i++) {
         Mat filteredImage = gaussianFilter2d(image, sigma1[i], sigma2[i]);
         assert(filteredImage.rows == n1 && filteredImage.cols == n2);
         ssr[i] = filteredImage;
         assert(ssr[i].rows == n1 && ssr[i].cols == n2);
     }
     return ssr;
}


Mat weightedLaplacian(const Mat& image, const double t1, const double t2){
    /**
     @brief Evaluates the weighted Laplacian of a given image.
     */
    // First compute derivative in x-direction.
    Mat outImage1;
    Mat outImage2;
    Mat outImage;
    Sobel(image, outImage1, -1, 2, 0);
    Sobel(image, outImage2, -1, 0, 2);
    addWeighted(outImage1, t1, outImage2, t2, 0, outImage);
    return outImage;
}


vector<Mat> scaleNormalizedLaplacian(const vector<Mat>& ssr, const vector<double>& sigma1, vector<double>& sigma2){
    /**
     @brief Evaluates the scale-normalized Laplacian of a given scale-space representation.
     @param[ssr] The scale-space representation. Of shape (k, m, n), where k is the number of scales.
     @param[sigma1] The vertical standard deviations corresponding to the scale-space representation. Must have length k.
     @param[sigma2] The horizontal standard deviations corrresponding to the scale-space representation. Must have length k.
     @returns The scale-normalized Laplacian, i.e. a 3D-array of shape (k, m, n).
     */
     // Initialize t1, t2-variable.
     double t1, t2;
     // Initialize normalized Laplacian.
     int numScales = ssr.size();
     vector<Mat> normLapSSR(numScales);
     for (int i=0; i<numScales; i++){
         t1 = sigma1[i] * sigma1[i];
         t2 = sigma2[i] * sigma2[i];
         Mat wl_i = weightedLaplacian(ssr[i], t1, t2);
         normLapSSR[i] = wl_i;
     }
     // Compute (t_1 * partial_1^2 + t_2 * partial_2^2) f to each scale-slice f of ssr.
     // Return the result as vector of matrices.
     return normLapSSR;
}


#endif //BLOBS_CPP_SCALESPACEREPRESENTATION_H
