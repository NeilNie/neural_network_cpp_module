//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_LAYER_H
#define FINAL_PROJECT_LAYER_H

#include <string>
#include "../../../src/LibNeuralNets.h"

class Layer {

public:

    int in_dim;
    int out_dim;
    std::string name;
    nn::Mat<float> weights;
    nn::Mat<float> biases;

    virtual ~Layer() = default;
    virtual nn::Mat<float> forward(nn::Mat<float>& input) { return {}; };

};


#endif //FINAL_PROJECT_LAYER_H
