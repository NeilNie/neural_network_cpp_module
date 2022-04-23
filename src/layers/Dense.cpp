//
// Created by Yongyang Nie on 4/1/22.
//

#include "libNeuralNets/layers/Layer.h"
#include "libNeuralNets/layers/Dense.h"

Eigen::MatrixX<float> Dense::forward(Eigen::MatrixX<float> &input) {

    // check for sizes
    if (input.rows() != weights.rows()) {
        throw std::invalid_argument("Input matrix size and weights size mismatch");
    }

    // matrix multiply
    Eigen::MatrixX<float> output = weights.transpose() * input + biases;

    // return
    return output;
}
