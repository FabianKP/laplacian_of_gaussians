//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_GAUSSIANBLOB_H
#define BLOBS_CPP_GAUSSIANBLOB_H

class GaussianBlob
{
    /**
     * This class represents a Gaussian scale-space blob.
     * A Gaussian scale-space blob is defined via 5 numbers:
     *  - 2 numbers for its location in 2d.
     *  - 2 numbers for its vertical/horizontal scale.
     *  - 1 number in [0, pi/2) for its angle.
     */
public:
    // GaussianBlob has no default constructor.
    GaussianBlob(double x1, double x2, double sigma1, double sigma2, double angle){
        /**
        * Constructor.
        */
        _x1 = x1;
        _x2 = x2;
        _sigma1 = sigma1;
        _sigma2 = sigma2;
        _angle = angle;
    }

    double get_sigma1(){
        return _sigma1;
    }

    double get_sigma2(){
        return _sigma2;
    }

    double get_x1(){
        return _x1;
    }

    double get_x2(){
        return _x2;
    }

    double get_angle(){
        return _angle;
    }

    double get_log_value(){
        return _log_value;
    }

private:
    double _x1;         // Vertical location.
    double _x2;         // Horizontal location.
    double _sigma1;     // Vertical standard deviation.
    double _sigma2;     // Horizontal standard deviation.
    double _angle;      // Angle.
    double _log_value;  // The value of the scale-normalized Laplacian at that blob.
                        // This can be seen as measure for the strength of the blob in the image.
};


#endif //BLOBS_CPP_GAUSSIANBLOB_H
