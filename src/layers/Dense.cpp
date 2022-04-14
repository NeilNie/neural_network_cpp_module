//
// Created by Yongyang Nie on 4/1/22.
//

module LibNeuralNets;

class Dense: public Layer {

    Eigen::MatrixX<float> forward(Eigen::MatrixX<float> &input) override {

        // check for sizes
        if (input.rows() != weights.rows()) {
            throw std::invalid_argument("Input matrix size and weights size mismatch");
        }

        // matrix multiply
        Eigen::MatrixX<float> output = weights.transpose() * input + biases;

        // return
        return output;
    }

};
