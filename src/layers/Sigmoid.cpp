//
// Created by Yongyang Nie on 4/1/22.
//

module LibNeuralNets;

using namespace nn;

Mat<float> Sigmoid::forward(Mat<float> &input) {

    // compute the sigmoid function
    Mat<float> matExp;
    /* input.exp().evalTo(matExp); */
    /* matExp.array() = 1.f / (matExp.array() + 1.f); */

    // return
    return matExp;
}
