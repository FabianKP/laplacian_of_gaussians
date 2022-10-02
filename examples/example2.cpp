//
// Created by fabian on 02.10.22.
// Example for use of LoG
//


#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "blobs.hpp"


using namespace cv;


int main(){
    // First, apply LoG to get blobs.
    // Load M54 test image.
    String imageFile = "hubble.jpg";
    ifstream ifile;
    ifile.open(imageFile);
    Mat testImage = imread( imageFile, IMREAD_GRAYSCALE);
    resize(testImage, testImage, Size(), 0.5, 0.5);
    testImage.convertTo(testImage, CV_32FC1);
    normalize(testImage, testImage, 0, 1, NORM_MINMAX);
    // Get scales.
    vector<double> sigmas;
    for (int i=2; i<20; i++){
        sigmas.push_back(i);
    }
    // Apply LoG.
    tuple<BlobList, BlobList> blobs = LoG(testImage, sigmas, 0.02, 0.2);
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);
    // Now, call paintBlobs-function.
    paintBlobs(testImage, brightBlobs, BlobList());
    return 0;
}
