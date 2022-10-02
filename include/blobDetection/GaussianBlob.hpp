//
// Created by fabian on 24.06.22.
//

#ifndef BLOBS_CPP_GAUSSIANBLOB_HPP
#define BLOBS_CPP_GAUSSIANBLOB_HPP


/**
    * @class Represents a Gaussian scale-space blob.
    * A Gaussian scale-space blob is defined via 4 numbers:
    *  - 2 numbers for its location in 2d.
    *  - 1 number for its standard deviation (square-root of the scale).
    *  - 1 number for its "strength", i.e. the value of the scale-normalized Laplacian at the blob.
    */
class GaussianBlob
{
public:
    /**
     * @brief Constructor.
     * @param x1 Row at which the blob is located.
     * @param x2 Column at which the blob is located.
     * @param sigma Standard deviation associated to the blob.
     * @param log_value The value of the scale-normalized Laplacian associated to the blob.
     */
    GaussianBlob(int x1, int x2, double sigma, float strength){
        m_x1 = x1;
        m_x2 = x2;
        m_sigma = sigma;
        m_strength = strength;
    }

    /**
     * @brief Returns standard deviation.
     */
    [[nodiscard]] double getSigma() const{
        return m_sigma;
    }

    /**
     * @brief Returns row of blob.
     */
    [[nodiscard]] int getX1() const{
        return m_x1;
    }

    /**
     * @brief Returns column of blob.
     */
    [[nodiscard]] int getX2() const{
        return m_x2;
    }

    /**
     * @brief Returns radius of circle associated to blob (r = sqrt(2) * sigma).
     */
    [[nodiscard]] double getRadius() const{
        return sqrt(2) * m_sigma;
    }

    /**
     * @brief Returns strength of blob (value of scale-normalized Laplacian).
     */
    [[nodiscard]] float getStrength() const{
        return m_strength;
    }

    /**
     * @brief Comparison for blobs. A blob is larger if the absolute value of its strength is larger.
     */
    bool operator <(const GaussianBlob &b) const{
        return (abs(m_strength) < abs(b.getStrength()));
    }

private:
    int m_x1;         // Vertical location.
    int m_x2;         // Horizontal location.
    double m_sigma;     // Standard deviation.
    float m_strength;  /* The value of the scale-normalized Laplacian at that blob.
                        * This can be seen as measure for the strength of the blob in the image. */
};


#endif //BLOBS_CPP_GAUSSIANBLOB_HPP
