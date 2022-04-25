//
// Created by Yongyang Nie on 4/1/22.
//


#include "../../include/libNeuralNets/layers/Dense.h"

nn::Mat<float> Dense::forward(nn::Mat<float> &input) {

    if (weights.size() == 0 || biases.size() == 0) {
        throw std::runtime_error("Dense layer weights and/or biases not initialized");
    }

    // check for sizes
    if (input.n_rows() != weights.n_rows()) {
        throw std::invalid_argument("Input matrix size and weights size mismatch");
    }

    // matrix multiply
    nn::Mat<float> output = weights.t() * input + biases;

    // return
    return output;
}

Dense::Dense(const std::string& layer_name,
             const nn::Mat<float> &init_weights,
             const nn::Mat<float> &init_biases) {

    name = layer_name;
    weights = init_weights;
    biases = init_biases;
}
