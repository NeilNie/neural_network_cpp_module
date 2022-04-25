//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_SIGMOID_H
#define FINAL_PROJECT_SIGMOID_H

#include "Layer.h"

class Sigmoid: public Layer {

public:
    nn::Mat<float> forward(nn::Mat<float> &input) override;
};


#endif //FINAL_PROJECT_SIGMOID_H
