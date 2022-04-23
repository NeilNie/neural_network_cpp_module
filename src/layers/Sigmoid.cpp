//
// Created by Yongyang Nie on 4/1/22.
//

#include <unsupported/Eigen/MatrixFunctions>
#include "libNeuralNets/layers/Layer.h"

class Sigmoid: public Layer {

    Eigen::MatrixX<float> forward(Eigen::MatrixX<float> &input) override {

        // compute the sigmoid function
        Eigen::MatrixX<float> matExp;
        input.exp().evalTo(matExp);
        matExp.array() = 1.f / (matExp.array() + 1.f);

        // return
        return matExp;
    }
};