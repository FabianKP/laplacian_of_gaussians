//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_LOG_H
#define BLOBS_CPP_LOG_H

#include <opencv2/opencv.hpp>
#include <cmath>
#include "GaussianBlob.h"
#include "scaleSpaceRepresentation.h"
#include "strictLocalMaximizer3D.h"
#include "checkOverlap.h"

using namespace cv;
using namespace std;
using BlobList = deque<GaussianBlob>;


/**
 * From a vector of extrema of the scale-normalized Laplacian, creates a list of the corresponding GaussianBlob-
 * objects.
 *
 * @param minimizers The vector of extrema.
 * @param sigma The vector of standard deviations used.
 * @return A vector of GaussianBlob-objects corresponding to the minimizers.
 */
BlobList extremaToBlobs(const vector<CriticalPoint>& minimizers, const vector<double>& sigma){
    BlobList blobs;
    for (const auto& point : minimizers){
        GaussianBlob blob(point.i, point.j, sigma[point.k],abs(point.val));
        blobs.push_back(blob);
    }
    return blobs;
}


/**
 * Remove all blobs with strength below a given relative threshold. This is done inplace.
 *
 * @param blobs The list of blobs.
 * @param rthresh The relative threshold. The absolute threshold is obtained by multiplying this with the strength
 *  of the strongest blob.
 */
void removeBelowThreshold(BlobList& blobs, double rthresh){
    // First, determine the maximum log_value. Since the blobs are sorted, this is the log_value of the first element.
    const float max_log = blobs[0].getStrength();
    // Remove all blobs with log-value less than rthresh * max_log.
    blobs.erase(remove_if(
            blobs.begin(), blobs.end(),
            [rthresh, max_log](const GaussianBlob& blob){
                return double(blob.getStrength()) < rthresh * double(max_log);
            }), blobs.end());
}


/**
 * Removes overlap. If the relative overlap of two blobs is larger than maxOverlap, the weaker blob is deleted.
 *
 * @param blobs The list of possibly overlapping blobs.
 * @param maxOverlap The maximum allowed relative overlap (i.e. a number between 0 and 1).
 */
void removeOverlap(BlobList& blobs, const double maxOverlap){
    // The strategy is a simple quadratic comparison. First compare the strongest blob to everyone else and remove all
    // intersecting blobs. Then, do the same for the second-strongest of the remaining blobs, and so on.
    deque<GaussianBlob> cleanedBlobs;
    while (blobs.size() >= 1) {
        // Remove the strongest blob from the list and put it into the cleaned list.
        GaussianBlob strongestBlob = blobs[0];
        cleanedBlobs.push_back(strongestBlob);
        blobs.pop_front();
        // Remove all blobs that have too much overlap with the strongest blob.
        blobs.erase(remove_if(
                blobs.begin(), blobs.end(),
                [strongestBlob, maxOverlap](const GaussianBlob &blob) {
                    return checkOverlap(strongestBlob, blob, maxOverlap);
                }), blobs.end());
    }
    // Finally, the original blob list is set equal to the cleaned blob list.
    blobs = cleanedBlobs;
}


/**
 * Performs blob detection using the Laplacian-of-Gaussians method. Only detects bright (high-intensity) blobs.
 *
 * @param input The input image. Must be 2-dimensional.
 * @param sigma The vector of standard deviations.
 * @param rthresh Relative threshold for detection. Must be between 0 and 1.
 *  A blob is detected if the corresponding scale-normalized Laplacian is less than rthresh times the global minimum.
 * @param maxOverlap Maximal overlap for detected blobs. Must be between 0 and 1.
 *  If two detected blobs have a relative overlap larger than this, then the weaker one is removed.
 * @return A list of the GaussianBlob objects, each corresponding to an identified blob.
 */
BlobList LoGBright(const Mat& input, const vector<double>& sigma, const double rthresh=0.01,
                   double maxOverlap=0.5){
    // Check input for consistency.
    int indims = input.dims;
    if (indims != 2){
        cerr << "Atm, LoG only works on 2-dimensional images." << endl;
    }
    // Since LoG currently only works for float-images, have to convert input.
    Mat image;
    input.convertTo(image, CV_32FC1);
    normalize(image, image, 0, 1, cv::NORM_MINMAX);
    // Create scale-space representation of the input image.
    vector<Mat> ssr = scaleSpaceRepresentation(image, sigma, sigma);
    // Evaluate scale-normalized Laplacian.
    vector<Mat> snl = scaleNormalizedLaplacian(ssr, sigma);
    //Mat snl = scaleNormalizedLaplacian(ssr, sigma1, sigma2);
    // Determine local maxima of the scale-normalized Laplacian in scale-space.
    vector<CriticalPoint> scaleSpaceMinimizers = strictLocalMinimizer3D(snl);
    // Convert local minima to GaussianBlob-instances.
    BlobList blobs = extremaToBlobs(scaleSpaceMinimizers, sigma);
    // Sort blobs in descending order according to their strength (this is useful for the next steps).
    sort(blobs.begin(), blobs.end());  // Possible, since we have overloaded "<"-operator.
    reverse(blobs.begin(), blobs.end());
    // Remove the blobs below the relative threshold.
    removeBelowThreshold(blobs, rthresh);
    // Remove overlap.
    removeOverlap(blobs, maxOverlap);
    return blobs;
}


/**
 * Performs blob detection using the Laplacian-of-Gaussians method. Detects both bright and dark blobs at the same time.
 *
 * @param input The input image. Must be 2-dimensional.
 * @param sigma The vector of standard deviations.
 * @param rthresh Relative threshold for detection. Must be between 0 and 1.
 *  A blob is detected if the corresponding scale-normalized Laplacian is less than rthresh times the global minimum.
 * @param maxOverlap Maximal overlap for detected blobs. Must be between 0 and 1.
 *  If two detected blobs have a relative overlap larger than this, then the weaker one is removed.
 * @return Returns two BlobList-objects. The first list contains the detected bright blobs (i.e. high-intensity blobs),
 *  the second list contains the deteced dark blobs.
 */
tuple<BlobList, BlobList> LoG(const Mat& input, const vector<double>& sigma, const double rthresh=0.01,
             double maxOverlap=0.5){
     // First, detect bright blobs.
     BlobList brightBlobs = LoGBright(input, sigma, rthresh, maxOverlap);
     // Detect dark blobs by detecting blobs in the negative image.
     BlobList darkBlobs = LoGBright(-input, sigma, rthresh);
     // Return both list of bright blobs and dark blobs.
     return make_tuple(brightBlobs, darkBlobs);
}


#endif //BLOBS_CPP_LOG_H
