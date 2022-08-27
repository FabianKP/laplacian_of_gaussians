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



void addCircle(const BlobList& blobs, Mat& image, const Scalar& color){
    for (const auto& blob : blobs){
        Point center(blob.get_x2(), blob.get_x1());
        double radius = blob.radius();
        int thickness = 1;
        circle(image, center, radius, color, thickness);
    }
}


void paintBlobs(const Mat& image, const tuple<BlobList, BlobList >& blobs){
    /**
     * Visualizes the given blobs as circles in the image.
     */
     // Make sure that the image has right format and scale.
     Mat convertedImage;
     image.convertTo(convertedImage, CV_32FC1);
     normalize(convertedImage, convertedImage, 0, 1, NORM_MINMAX);
     // For each blob, draw circle.
     BlobList brightBlobs = get<0>(blobs);
     BlobList darkBlobs = get<1>(blobs);
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



#endif //BLOBS_CPP_PAINTBLOBS_H
