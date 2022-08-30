//
// Created by fabian on 27.08.22.
//

#ifndef BLOBS_CPP_PAINTBLOBS_H
#define BLOBS_CPP_PAINTBLOBS_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "GaussianBlob.h"

using namespace cv;
using namespace std;


/**
 * Draws a circle corresponding to a given blob in a given image. This is done inplace.
 *
 * @param blobs A GaussianBlob-object.
 * @param image The given image on which a circle shall be drawn.
 * @param color The color-code for the circle border. For example, color = Scalar(255, 0, 0) yields a blue circle.
 */
void addCircle(const BlobList& blobs, Mat& image, const Scalar& color){
    for (const auto& blob : blobs){
        Point center(blob.getX2(), blob.getX1());
        double radius = blob.getRadius();
        int thickness = 1;
        circle(image, center, radius, color, thickness);
    }
}


/**
 * Visualizes blobs by drawing corresponding circles in the given image. This is done inplace.
 *
 * @param image The image on which the blobs shall be drawn. Must be 2-dimensional.
 * @param brightBlobs A list of detected high-intensity blobs.
 * @param darkBlobs A list of detected low-intensity blobs.
 */
void paintBlobs(Mat& image, const BlobList& brightBlobs = BlobList(), const BlobList& darkBlobs = BlobList()){
    // Make sure that the image has right format and scale.
    Mat convertedImage;
    image.convertTo(convertedImage, CV_32FC1);
    normalize(convertedImage, convertedImage, 0, 1, NORM_MINMAX);
    // Convert image to color.
    cvtColor(convertedImage, convertedImage, COLOR_GRAY2BGR);
    // For each blob, draw circle.
    // Bright blobs are visualized with green circles.
    Scalar green(0, 255, 0);
    addCircle(brightBlobs, convertedImage, green);
    // Dark blobs are visualized with red circles.
    Scalar red(0, 0, 255);
    addCircle(darkBlobs, convertedImage, red);
    namedWindow("Image with blobs", WINDOW_NORMAL);
    imshow("Image with blobs", convertedImage);
    waitKey(0);
}


/**
 * @overload Of paintBlobs for passing bright and dark blobs as tuple.
 *
 * @param image The image on which the blobs shall be drawn. Must be 2-dimensional.
 * @param blobs The first tuple element corresponds to bright blobs, the second to dark blobs.
 */
void paintBlobs(Mat& image, const tuple<BlobList, BlobList>& blobs){
    // Extract blobs and then call corresponding version of this function.
    const BlobList& brightBlobs = get<0>(blobs);
    const BlobList& darkBlobs = get<1>(blobs);
    paintBlobs(image, brightBlobs, darkBlobs);
}



#endif //BLOBS_CPP_PAINTBLOBS_H
