//
// Created by Yongyang Nie on 4/1/22.
//

module LibNeuralNets;

import <cmath>;

using namespace nn;

Mat<float> Sigmoid::forward(const Mat<float>& input) const
{
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

    auto output = input;

    // compute the sigmoid function
    for (size_t r = 0; r < input.n_rows(); r++) {
        for (size_t c = 0; c < input.n_cols(); c++) {
            output(c, r) = 1.f / (::expf(-input(c, r)) + 1.f);
        }
    }
    // return
    return output;
}
