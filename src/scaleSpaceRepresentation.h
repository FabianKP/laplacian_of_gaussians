//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_SCALESPACEREPRESENTATION_H
#define BLOBS_CPP_SCALESPACEREPRESENTATION_H

#include <cstdlib>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


Mat scaleSpaceRepresentation(const Mat& image, const vector<double>& sigma1, const vector<double>& sigma2){
    /**
     @brief Given an image and a list of scales, creates the Gaussian scale-space representation.
     @param[image] The input image. Must be 2-dimensional and grayscale.
     @param[sigma1] The list of vertical standard deviations.
     @param[sigma2] The list of horizontal standard deviations.
     @return Returns the 3-dimensional scale-space representation.
     */
     // Check input for consistency.
     // The image must be 2-dimensional and grayscale.
     // sigma1 and sigma2 must have the same length.
     // Compute scale-space representation by filtering the image multiple times.
     // Perform sanity checks.
     // Return the scale-space representation.
}


Mat scaleNormalizedLaplacian(const Mat& ssr, const vector<double>& sigma1, const vector<double>& sigma2){
    /**
     @brief Evaluates the scale-normalized Laplacian of a given scale-space representation.
     @param[ssr] The scale-space representation. Of shape (k, m, n), where k is the number of scales.
     @param[sigma1] The vertical standard deviations corresponding to the scale-space representation. Must have length k.
     @param[sigma2] The horizontal standard deviations corrresponding to the scale-space representation. Must have length k.
     @returns The scale-normalized Laplacian, i.e. a 3D-array of shape (k, m, n).
     */
     // Get t-values corresponding to sigma1, sigma2.
     // Compute t * Delta f to each scale-slice f of ssr.
     // Return the result as 3D-matrix.
}


#endif //BLOBS_CPP_SCALESPACEREPRESENTATION_H
