//
// Created by Yongyang Nie on 4/1/22.
//

#include "libNeuralNets/module/Module.h"

Module::Module(std::string model_path, std::vector<std::string> layer_names) {

    layers = std::vector<Layer>();
    for (const auto& name: layer_names) {
        std::string bias_path = "/model_weights/" + name + "/" + name + "/bias:0";
        std::string weights_path = "/model_weights/" + name + "/" + name + "/kernel:0";
        Eigen::VectorXf bias;
        Eigen::MatrixXf weights;
        Module::read_2D_data_to_matrix(model_path, weights_path, weights);
        Module::read_1D_vector(model_path, bias_path, bias);

        if (name.find("dense") != std::string::npos) {
            

        } else if  (name.find("sigmoid") != std::string::npos) {

        } else {
            throw std::invalid_argument("Module constructor received invalid layer name");
        }
    }
}

Module::Module(std::vector<Layer> layers) {

}
