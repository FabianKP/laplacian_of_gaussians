

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "blobDetection.hpp"


using namespace cv;


int main(){
    // To test the blob detection method, we use an image of galaxies.
    String imageFile = "hubble.jpg";
    // Check that the file exists.
    ifstream ifile;
    ifile.open(imageFile);
    // Load the image into an OpenCV matrix.
    Mat testImage = imread( imageFile, IMREAD_GRAYSCALE);
    // Make the image a bit smaller to speed up the code.
    resize(testImage, testImage, Size(), 0.5, 0.5);
    testImage.convertTo(testImage, CV_32FC1);
    // Normalize for better plotting.
    normalize(testImage, testImage, 0, 1, NORM_MINMAX);
    // Next we want to apply the Laplacian-of-Gaussians method for blob detection. For this we have to set the
    // scales we want to look at.
    double sigmaMin {2};
    double sigmaMax {20};
    int numSigma {19};
    // We also have to set the threshold for blob detection and the maximum relative overlap for detected blobs.
    // Check the doc-string of the `LoG` function to find out more about those.
    double rthresh {0.02};
    double maxOverlap {0.2};
    // Now we can perform blob detection.
    tuple<BlobList, BlobList> blobs = LoG(testImage, sigmaMin, sigmaMax, numSigma, rthresh, maxOverlap);
    // The LoG method returns a tuple of two `BlobList`-objects, corresponding to the detected bright and dark blobs.
    BlobList brightBlobs = get<0>(blobs);
    BlobList darkBlobs = get<1>(blobs);
    /* For visualization of the detected blobs, we can use the 'paintBlobs' function provided by 'blobs.hpp'. Since in
     * this case we are only interested in the bright blobs, we ignore 'darkBlobs'. If we would be interested in
     * plotting both bright and dark blobs, we could call 'paintBlobs' instead with the tuple 'blobs'. */
    Mat imageWithBlobs = paintBlobs(testImage, brightBlobs);
    // The function 'paintBlobs' returns the test image with the detected blobs drawn on it.
    // Let us plot both the original image and the image with the detected blobs.
    String nameOrig = "Original image";
    String nameBlobs = "Image with blobs";
    namedWindow(nameOrig, WINDOW_NORMAL);
    namedWindow(nameBlobs, WINDOW_NORMAL);
    imshow(nameOrig, testImage);
    imshow(nameBlobs, imageWithBlobs);
    // Press Enter to close windows.
    waitKey(0);
    destroyWindow(nameOrig);
    destroyWindow(nameBlobs);
    imwrite("hubble_small.jpg", 255 * testImage);
    imwrite("hubble_with_blobs.jpg", 255 * imageWithBlobs);
    return 0;
}
