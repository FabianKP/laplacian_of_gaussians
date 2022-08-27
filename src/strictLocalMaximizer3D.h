
//
// Created by fabian on 18.08.22.
//

#ifndef BLOBS_CPP_STRICTLOCALMAXIMIZER3D_H
#define BLOBS_CPP_STRICTLOCALMAXIMIZER3D_H


using namespace std;
using namespace cv;


struct CriticalPoint{
    int k;
    int i;
    int j;
    float val;
};


vector<vector<vector<float>>> matToArray3D(const vector<Mat>& input){
    /**
     * Given a 3D opencv mat, returns a 3D C++ array.
     */
     // Convert stack to 3D array, slice-wise.
    int l = input.size();
    int m = input[0].rows;
    int n = input[0].cols;
    // Initialize 3D-vector
    vector<vector<vector<float>>> mat3d;
    mat3d.reserve(l);
    for (int k=0; k<l; k++ ) {
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


float getMaxOfNeighbours(const vector<vector<vector<float>>>& input, int k, int i, int j){
    /**
     * Computes the maximum intensity of all neighbours of a given pixel.
     */
     // Fill vector with neighbour intensities.
     // We know that there will not be more than 28 neighbours.
     float neighbourIntensities[28] {0};
     int counter = 0;
     int L = input.size();
     for (int k2 = max(k-1, 0); k2 <= min(k+1, L-1); k2++){
         int M = input[k2].size();
         for(int i2 = max(i-1, 0); i2 <= min(i+1, M-1); i2++){
             int N = input[k2][i2].size();
             for(int j2 = max(j-1, 0); j2 <= min(j+1, N-1); j2++){
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


vector<CriticalPoint> strictLocalMaximizer3D(const vector<vector<vector<float>>>& input){
    /**
     * Finds strict local maximizers of given 3D-image.
     */
     // Initialize list of local maximizers.
     vector<CriticalPoint> localMaximizers;
     // Iterate over all voxels. Compare each voxel with its 7-28 neighbours. If it is strictly larger then all of them,
     // add its position to localMaximizers.
     int L = input.size();
     for (int k=0; k<L; k++){
         int M = input[k].size();
         for (int i=0; i<M; i++){
             int N = input[k][i].size();
             for (int j=0; j<N; j++){
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


vector<CriticalPoint> strictLocalMaximizer3D(const vector<Mat>& input){
    /**
     * Finds strict local maximizers by finding strict local maximizers of negative image.
     */
     // First, convert input into 3D-array.
     int L = input.size();
     assert(L > 0);
     vector<vector<vector<float>>> input3d = matToArray3D(input);
     return strictLocalMaximizer3D(input3d);
}


vector<CriticalPoint> strictLocalMinimizer3D(const vector<Mat> input){
    int L = input.size();
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
