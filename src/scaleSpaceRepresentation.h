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


/**
 * Given an image and a list of scales, creates the Gaussian scale-space representation.
 *
 * @param image The input image. Must be 2-dimensional. The image is converted to grayscale, so any color-information
 *  is ignored.
 * @param sigma1 The list of vertical standard deviations.
 * @param sigma2 The list of horizontal standard deviations.
 * @return Returns the 3-dimensional scale-space representation.
 */
vector<Mat> scaleSpaceRepresentation(const Mat& image, const vector<double>& sigma1, const vector<double>& sigma2){
     // Check input for consistency. The image must be 2-dimensional and grayscale.
     assert(image.depth()==CV_32FC1);
     assert(image.dims == 2 && image.channels() == 1);
     // sigma1 and sigma2 must have the same length.
     assert(sigma1.size() == sigma2.size());
     int k = sigma1.size();
     int n1 = image.rows;
     int n2 = image.cols;
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


/**
 * Evaluates weighted Laplacian for a given image.
 *
 * @param image The input image.
 * @param t The scale-parameter.
 * @return Returns an image of the same shape as the input-image, containing the result of t * Laplacian(image).
 */
Mat weightedLaplacian(const Mat& image, const double t){
    // First compute derivative in x-direction.
    Mat outImage;
    Laplacian(image, outImage, -1, 1, 1);
    outImage = t * outImage;
    return outImage;
}


/**
 * Evaluates the scale-normalized Laplacian of a 3-dimensional array scale-space object.
 *
 * @param ssr The scale-space object. Should be a vector of equally-shaped 2-dimensional images.
 * @param sigma The standard deviations corresponding to the scale-axis. Must be of the same length as ssr.
 * @return Returns a 3-dimensional scale-space object of the same format as ssr. This is the result of applying the
 *  3-dimensional scale-normalized Laplacian to ssr.
 */
vector<Mat> scaleNormalizedLaplacian(const vector<Mat>& ssr, const vector<double>& sigma){
    assert(ssr[0].depth()==CV_32FC1);
     // Initialize t1, t2-variable.
     double t;
     // Initialize normalized Laplacian.
     int numScales = ssr.size();
     vector<Mat> normLapSSR(numScales);
     for (int i=0; i<numScales; i++){
         t = sigma[i] * sigma[i];
         Mat wl_i = weightedLaplacian(ssr[i], t);
         normLapSSR[i] = wl_i;
     }
     // Compute (t_1 * partial_1^2 + t_2 * partial_2^2) f to each scale-slice f of ssr.
     // Return the result as vector of matrices.
     return normLapSSR;
}


#endif //BLOBS_CPP_SCALESPACEREPRESENTATION_H
