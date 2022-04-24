//
// Created by Yongyang Nie on 4/1/22.
//

#include <unsupported/Eigen/MatrixFunctions>
#include "../../include/libNeuralNets/layers/Sigmoid.h"

Eigen::MatrixX<float> Sigmoid::forward(Eigen::MatrixX<float> &input) {

    // compute the sigmoid function
    Eigen::MatrixX<float> matExp;
    input.exp().evalTo(matExp);
    matExp.array() = 1.f / (matExp.array() + 1.f);

    // return
    return matExp;
}