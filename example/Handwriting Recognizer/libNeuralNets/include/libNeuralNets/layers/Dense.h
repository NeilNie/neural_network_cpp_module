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
          const nn::Mat<float> &init_weights,
          const nn::Mat<float> &init_biases);

    // forward method override
    nn::Mat<float> forward(nn::Mat<float> &input) override;

};

#endif //FINAL_PROJECT_DENSE_H
