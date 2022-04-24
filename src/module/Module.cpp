//
// Created by Yongyang Nie on 4/1/22.
//

#include "../../include/libNeuralNets/module/Module.h"

Module::Module(const std::string& model_path, const std::vector<std::string>& names) {

    /**
     *
     * @param model_path
     * @param layer_names
     */
    layers = std::vector<Layer>();
    for (const auto& name: layer_names) {
        std::string bias_path = "/model_weights/" + name + "/" + name + "/bias:0";
        std::string weights_path = "/model_weights/" + name + "/" + name + "/kernel:0";
        Eigen::VectorXf bias;
        Eigen::MatrixXf weights;
        Module::read_2D_data_to_matrix(model_path, weights_path, weights);
        Module::read_1D_vector(model_path, bias_path, bias);

        if (name.find("dense") != std::string::npos) {
            auto layer = Dense(name, weights, bias);
            layers.push_back(layer);
        } else if  (name.find("sigmoid") != std::string::npos) {
            auto layer = Sigmoid();
            layers.push_back(layer);
        } else {
            throw std::invalid_argument("Module constructor received invalid layer name");
        }
        layer_names.push_back(name);
    }
}

Module::Module(std::vector<Layer> layers) {

}

Eigen::MatrixXf Module::forward(const Eigen::MatrixXf &input) {

    /**
     *
     * Run forward feed on all layers
     *
     * @param input The input tensor.
     * @return The resulting tensor after running
     * forward feeding on all existing layers.
     */

    if (layers.empty())
        throw std::runtime_error("Module instance layers "
                                 "variable has not been "
                                 "initialized.");

    Eigen::MatrixXf value = input;
    for (auto layer: layers)
        value = layer.forward(value);
    return value;
}
