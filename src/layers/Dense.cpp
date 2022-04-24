//
// Created by Yongyang Nie on 4/1/22.
//


#include <Eigen/Dense>
#include "../../include/libNeuralNets/layers/Dense.h"

Eigen::MatrixX<float> Dense::forward(Eigen::MatrixX<float> &input) {

    if (weights.size() == 0 || biases.size() == 0) {
        throw std::runtime_error("Dense layer weights and/or biases not initialized");
    }

    // check for sizes
    if (input.rows() != weights.rows()) {
        throw std::invalid_argument("Input matrix size and weights size mismatch");
    }

    // matrix multiply
    Eigen::MatrixX<float> output = weights.transpose() * input + biases;

    // return
    return output;
}

Dense::Dense(const std::string& layer_name,
             const Eigen::MatrixXf &init_weights,
             const Eigen::VectorXf &init_biases) {

    name = layer_name;
    weights = init_weights;
    biases = init_biases;
}
