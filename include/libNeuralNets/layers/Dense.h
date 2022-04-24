//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_DENSE_H
#define FINAL_PROJECT_DENSE_H


#include "Layer.h"

class Dense: public Layer {

public:

    // instance initializer
    Dense(const std::string& layer_name,
          const Eigen::MatrixXf &init_weights,
          const Eigen::VectorXf &init_biases);

    // forward method override
    Eigen::MatrixX<float> forward(Eigen::MatrixX<float> &input) override;

};

#endif //FINAL_PROJECT_DENSE_H
