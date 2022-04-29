//
// Created by Yongyang Nie on 4/1/22.
//

module LibNeuralNets;

import <iostream>;
import <stdexcept>;

using namespace nn;

Mat<float> Dense::forward(const Mat<float>& input) const
{
    // check for sizes
    if (input.n_rows() != weights_.n_rows())
        throw std::invalid_argument("Input matrix size and weights size mismatch");

    // matrix multiply
    Mat<float> output = weights_.t() * input + biases_;

    // return
    return output;
}
