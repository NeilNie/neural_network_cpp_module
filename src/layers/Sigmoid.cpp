//
// Created by Yongyang Nie on 4/1/22.
//

#include <cmath>
#include "../../include/libNeuralNets/layers/Sigmoid.h"

nn::Mat<float> Sigmoid::forward(nn::Mat<float> &input) {

    /**
     *
     * Perform element wise sigmoid operation on the input matrix.
     * The sigmoid operation is define as:
     *
     *       out = 1 / (e^{-input} + 1)
     *
     * @param input
     * @return Matrix instance after performing element-wise
     * sigmoid operation
     */

    // compute the sigmoid function
    for (size_t r = 0; r < input.n_rows(); r++) {
        for (size_t c = 0; c < input.n_cols(); c++) {
            input(c, r) = 1.f / (expf(-input(c, r)) + 1.f);
        }
    }
    // return
    return input;
}