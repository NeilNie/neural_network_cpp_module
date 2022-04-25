//
// Created by Yongyang Nie on 4/1/22.
//

module LibNeuralNets;

import <stdexcept>;

using namespace nn;

Mat<float> Dense::forward(Mat<float> &input) {

    // check for sizes
    if (input.n_rows() != weights.n_rows()) {
        throw std::invalid_argument("Input matrix size and weights size mismatch");
    }

    // matrix multiply
    Mat<float> output = weights.t() * input + biases;

    // return
    return output;
}
