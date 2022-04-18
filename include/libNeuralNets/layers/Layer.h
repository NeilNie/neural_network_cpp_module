//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_LAYER_H
#define FINAL_PROJECT_LAYER_H

#include <Eigen/Dense>

class Layer {

public:

    int in_dim;
    int out_dim;
    Eigen::MatrixX<float> weights;
    Eigen::MatrixX<float> biases;

    virtual ~Layer();
    virtual Eigen::MatrixX<float> forward(Eigen::MatrixX<float>& input);

};


#endif //FINAL_PROJECT_LAYER_H
