//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_SIGMOID_H
#define FINAL_PROJECT_SIGMOID_H

#include "Layer.h"

class Sigmoid: public Layer {

public:
    Eigen::MatrixX<float> forward(Eigen::MatrixX<float> &input) override;
};


#endif //FINAL_PROJECT_SIGMOID_H
