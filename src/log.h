//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_LOG_H
#define BLOBS_CPP_LOG_H

#include <opencv2/opencv.hpp>
#include "GaussianBlob.h"
#include "scaleSpaceRepresentation.h"

using namespace cv;
using namespace std;
using BlobList = list<GaussianBlob>;


BlobList snlToBlobs(const Mat& snl, const vector<double>& sigma1, const vector<double>& sigma2){
    // To be implemented.
}


BlobList& removeBelowThreshold(BlobList& blobs, double rthresh){
    // Removes all that are too weak, where weakness is defined via is log-value.
}

BlobList& removeOverlap(BlobList& blobs, double maxOverlap){
    // Removes overlap by deleting weaker blob.
}


BlobList log(const Mat& input, const vector<double>& sigma1, const vector<double>& sigma2, const double rthresh=0.01,
                       double maxOverlap=0.5){
    /**
     @brief Performs blob detection using the Laplacian-of-Gaussians method.
     @param[input] The input image. Must be 2-dimensional.
     @param[sigma1] The vector of vertical standard deviations.
     @param[sigma2] The vector of horizontal standard deviations.
     @param[rthresh] Relative threshold for detection. Must be between 0 and 1.
        A blob is detected if the corresponding scale-normalized Laplacian is less than rthresh times the global minimum.
     @param[maxOverlap] Maximal overlap for detected blobs. Must be between 0 and 1.
        If two detected blobs have a relative overlap larger than
        this, then the weaker one is removed.
    @return A list of the GaussianBlob objects, each corresponding to an identified blob.
     */
     // Check input for consistency.
     int indims = input.dims;
     if (indims != 2){
         cerr << "Atm, LoG only works on 2-dimensional images." << endl;
     }
     if (sigma1.size() != sigma2.size()){
         cerr << "sigma1 and sigma2 must have same size." << endl;
     }
     // Create scale-space representation of the input image.
     vector<Mat> ssr = scaleSpaceRepresentation(input, sigma1, sigma2);
     // Evaluate scale-normalized Laplacian.
     vector<Mat> snl = scaleNormalizedLaplacian(ssr, sigma1, sigma2);
     //Mat snl = scaleNormalizedLaplacian(ssr, sigma1, sigma2);
     // Determine local minima of the scale-normalized Laplacian in scale-space.

     // Convert local minima to GaussianBlob-instances.
     //BlobList blobList = snlToBlobs(snl, sigma1, sigma2);
     // Remove the ones that are below the relative threshold.
     //removeBelowThreshold(blobList, rthresh);
     // Remove overlap.
     //removeOverlap(blobList, maxOverlap);
     // Perform sanity checks and return.
     // return blobList;
}




#endif //BLOBS_CPP_LOG_H
