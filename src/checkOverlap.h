//
// Created by fabian on 26.08.22.
//

#ifndef BLOBS_CPP_CHECKOVERLAP_H
#define BLOBS_CPP_CHECKOVERLAP_H

#include <cmath>
#include "GaussianBlob.h"

using namespace std;


double computeRelativeOverlap(const GaussianBlob& blob1, const GaussianBlob& blob2){
    /**
     * Computes relative overlap of two blobs.
     * The relative overlap is defined as the area of the intersection, divided by the area of the smaller blob.
     * We assume that the first blob is at least as large as the second one.
     */
    double relativeOverlap;
    // Compute area of intersection
    // (see https://diego.assencio.com/?index=8d6ca3d82151bad815f78addf9b5c1c6 for a derivation).
    // First, compute center distance.
    // Compute distance of blob centers.
    int dist1 = blob1.get_x1() - blob2.get_x1();
    int dist2 = blob1.get_x2() - blob2.get_x2();
    double d = sqrt(double(dist1 * dist1 + dist2 * dist2));
    // Get radii.
    double r1 = blob1.radius();
    double r2 = blob2.radius();
    // Compute area of smaller blob;
    double areaOfSmaller = M_PI * r2 * r2;
    // If d >= r1 + r2, the intersection area is 0.
    if (d >= r1 + r2){
        relativeOverlap = 0.;
    }
        // If d <= r1 - r2, then the smaller circle is contained in the larger one.
    else if(d <= r1 - r2){
        relativeOverlap = 1.;
    }
    else {
        double d1 = (r1*r1-r2*r2+d*d) / (2 * d);
        double d2 = d - d1;
        double a1 = r1*r1*acos(d1/r1) - d1*sqrt(r1*r1 - d1*d1);
        double a2 = r2*r2*acos(d2/r2) - d2*sqrt(r2*r2-d2*d2);
        double intersectionArea = a1 + a2;
        // Divide by area of smaller blob to get the relative overlap.
        relativeOverlap = intersectionArea / areaOfSmaller;
    }
    return relativeOverlap;
}


bool checkOverlap(const GaussianBlob& blob1, const GaussianBlob& blob2, double maxOverlap){
    /**
     * Checks whether the relative overlap of two given blobs is above threshold.
     */
    // Next, compute the relative overlap.
    double relativeOverlap = computeRelativeOverlap(blob1, blob2);
    // If the relative overlap is above maxOverlap, remove the blob from the list.
    return (relativeOverlap > maxOverlap);
}


#endif //BLOBS_CPP_CHECKOVERLAP_H
