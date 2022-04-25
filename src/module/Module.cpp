//
// Created by Yongyang Nie on 4/1/22.
//

#include "../../include/libNeuralNets/module/Module.h"

Module::Module(const std::string& model_path, const std::vector<std::string>& names) {

    /**
     *
     * @param model_path Path to the directory that contains
     * the model weights saved as txt files.
     * @param layer_names The names of the layers, which
     * should correspond to the file names on disk.
     */
    layers = std::vector<Layer>();

    for (const auto& name: names) {

        std::string bias_path = name + "_bias.txt";
        std::string weights_path = name + "_weights.txt";

        if (name.find("dense") != std::string::npos) {

            std::cout << "Loading layer: " << name << "\n";

            nn::Mat<float> bias;
            nn::Mat<float> weights;

            Module::read_txt_data_to_matrix(model_path, weights_path, weights);
            Module::read_txt_data_to_matrix(model_path, bias_path, bias);
            auto layer = Dense(name, weights, bias);
            layers.push_back(layer);
        } else if  (name.find("sigmoid") != std::string::npos) {
            std::cout << "Loading layer: " << name << "\n";
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

nn::Mat<float> Module::forward(const nn::Mat<float> &input) {

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

    nn::Mat<float> value = input;
    for (auto layer: layers)
        value = layer.forward(value);
    return value;
}
