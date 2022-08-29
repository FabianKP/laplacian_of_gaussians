
//
// Created by fabian on 18.08.22.
//

#ifndef BLOBS_CPP_STRICTLOCALMAXIMIZER3D_H
#define BLOBS_CPP_STRICTLOCALMAXIMIZER3D_H


using namespace std;
using namespace cv;


/**
 * Represents a critical point of a 3-dimensional array.
 */
struct CriticalPoint{
    ulong k;      // Position along the first axis.
    ulong i;      // Position along the second axis.
    ulong j;      // Position along the third axis.
    float val;  // Value of the array at the position (k, i, j).
};


/**
 * Converts a vector of 2-dimensional images into a 3-dimensional std-vector.
 * @param input A vector of equally-shaped 2-dimensional images.
 * @return A 3-dimensional std-vector of type float.
 */
vector<vector<vector<float>>> matToArray3D(const vector<Mat>& input){
     // Convert stack to 3D array, slice-wise.
    ulong l = input.size();
    int m = input[0].rows;
    int n = input[0].cols;
    // Initialize 3D-vector
    vector<vector<vector<float>>> mat3d;
    mat3d.reserve(l);
    for (ulong k=0; k<l; k++ ) {
        vector<vector<float>> matk;
        matk.reserve(m);
        for (int i = 0; i < m; ++i) {
            vector<float> rowki;
            rowki.reserve(n);
            rowki.insert(rowki.end(), input[k].ptr<float>(i),
                    input[k].ptr<float>(i) + n);
            matk.push_back(rowki);
        }
        mat3d.push_back(matk);
    }
    return mat3d;
}


/**
 * Computes the maximum intensity of all neighbours of a given voxel.
 *
 * @param input A 3-dimensional vector.
 * @param k Scale index.
 * @param i Row index.
 * @param j Column index.
 */
float getMaxOfNeighbours(const vector<vector<vector<float>>>& input, ulong k, ulong i, ulong j){
    /**
     * Computes the maximum intensity of all neighbours of a given pixel.
     */
     // Fill vector with neighbour intensities.
     // We know that there will not be more than 28 neighbours.
     float neighbourIntensities[28] {0};
     int counter = 0;
     ulong L = input.size();
     for (auto k2 = max(ulong(k-1), ulong(0)); k2 <= min((ulong)k+1, L-1); k2++){
         ulong M = input[k2].size();
         for(ulong i2 = max(ulong(i-1), ulong(0)); i2 <= min(i+1, M-1); i2++){
             ulong N = input[k2][i2].size();
             for(ulong j2 = max(ulong(j-1), ulong(0)); j2 <= min(j+1, N-1); j2++){
                 if (k2 != k || i2 != i || j2 != j) {
                     neighbourIntensities[counter] = input[k2][i2][j2];
                 }
                 counter++;
             }
         }
     }
     // Get maximum
    float maxIntensity = *max_element(begin(neighbourIntensities), end(neighbourIntensities));
    return maxIntensity;
}


/**
 * Finds all strict local maximizers of a given 3-dimensional vector. That is, it finds all points (k, i, j) such that
 * the value of the input at all neighbours is strictly less than the value at (k, i, j).
 *
 * @param input A 3-dimensional vector.
 * @return The list of maximizers, as vector of CriticalPoint-objects.
 */
vector<CriticalPoint> strictLocalMaximizer3D(const vector<vector<vector<float>>>& input){
     // Initialize list of local maximizers.
     vector<CriticalPoint> localMaximizers;
     // Iterate over all voxels. Compare each voxel with its 7-28 neighbours. If it is strictly larger then all of them,
     // add its position to localMaximizers.
     ulong L = input.size();
     for (ulong k=0; k<L; k++){
         ulong M = input[k].size();
         for (ulong i=0; i<M; i++){
             ulong N = input[k][i].size();
             for (ulong j=0; j<N; j++){
                 float value = input[k][i][j];
                 float neighbourMax = getMaxOfNeighbours(input, k, i, j);
                 if (value > neighbourMax) {
                     localMaximizers.push_back(CriticalPoint{k, i, j, value});
                 }
             }
         }
     }
     return localMaximizers;
}


/**
 * @overload Finds all strict local maximizers of an image-stack.
 *
 * @param input A 3-dimensional vector.
 * @return The list of maximizers, as vector of CriticalPoint-objects.
 */
vector<CriticalPoint> strictLocalMaximizer3D(const vector<Mat>& input){
    /**
     * Finds strict local maximizers by finding strict local maximizers of negative image.
     */
     // First, convert input into 3D-array.
     ulong L = input.size();
     assert(L > 0);
     vector<vector<vector<float>>> input3d = matToArray3D(input);
     return strictLocalMaximizer3D(input3d);
}


/**
 * Finds all strict local minimizers of a given image-stack, i.e. all points at which the intensity is strictly less
 * than at all of its neighbors. To this end, the stack is interpreted as a 3-dimensional vector.
 *
 * @param input A stack of two-dimensional matrices.
 * @return The list of maximizers, as vector of CriticalPoint-objects.
 */
vector<CriticalPoint> strictLocalMinimizer3D(const vector<Mat>& input){
    ulong L = input.size();
    assert(L > 0);
    // Negate every array.
    vector<Mat> neg_input;
    for (const auto& mat : input){
        neg_input.push_back(-mat);
    }
    vector<vector<vector<float>>> input3d = matToArray3D(neg_input);
    vector<CriticalPoint> minimizer = strictLocalMaximizer3D(input3d);
    // Have to change values so that everything is correct.
    for (auto& crit : minimizer){
        crit.val = -crit.val;
    }
    return minimizer;
}


#endif //BLOBS_CPP_STRICTLOCALMAXIMIZER3D_H
