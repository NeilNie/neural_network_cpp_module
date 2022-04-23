//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_DENSE_H
#define FINAL_PROJECT_DENSE_H

#include "libNeuralNets/layers/Layer.h"

class Dense: public Layer {

public:
    Eigen::MatrixX<float> forward(Eigen::MatrixX<float> &input) override;

};

#endif //FINAL_PROJECT_DENSE_H
