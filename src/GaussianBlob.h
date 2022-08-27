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
    GaussianBlob(int x1, int x2, double sigma, float log_value){
        /**
        * Constructor.
        */
        _x1 = x1;
        _x2 = x2;
        _sigma = sigma;
        _log_value = log_value;
    }

    double get_sigma() const{
        return _sigma;
    }


    int get_x1() const{
        return _x1;
    }

    int get_x2() const{
        return _x2;
    }

    double radius() const{
        return sqrt(2) * _sigma;
    }

    [[nodiscard]] float get_log_value() const{
        return _log_value;
    }

    bool operator <(const GaussianBlob &b) const{
        return (_log_value < b.get_log_value());
    }

private:
    int _x1;         // Vertical location.
    int _x2;         // Horizontal location.
    double _sigma;     // Standard deviation.
    float _log_value;  // The value of the scale-normalized Laplacian at that blob.
                        // This can be seen as measure for the strength of the blob in the image.
};


#endif //BLOBS_CPP_GAUSSIANBLOB_H
