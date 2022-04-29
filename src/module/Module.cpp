//
// Created by Yongyang Nie on 4/1/22.
//

module;

import <iostream>;
import <vector>;
import <string>;
import <stdexcept>;
import <system_error>;
import <memory>;
import <cstring>;
import <cstdio>;
import <cstdlib>;

module LibNeuralNets;

using namespace nn;

static constexpr char bias_txt_suffix[] = "_bias.txt";
static constexpr char weights_txt_suffix[] = "_weights.txt";

template <const char *DataPathSuffix, bool Verbose = true>
static inline void read_txt_data_to_matrix(const std::string& path,
                                    const std::string& data_path,
                                    nn::Mat<float>& out)
{
    // unfortunately must use C string semantics here, too much std::string
    // construction seems to incur compiler error in module
    std::unique_ptr<char[]> full_path(
            new char[path.length() + data_path.length() + std::strlen(DataPathSuffix) + 1]);
    std::sprintf(full_path.get(), "%s%s%s", path.c_str(), data_path.c_str(), DataPathSuffix);
    if constexpr (Verbose)
    std::cout << "Begin loading..." << "\n";

    out.load_from_txt(full_path.get());
}

Module::Module(const std::string& model_path, const std::vector<std::string>& names)
{
    /**
     *
     * @param model_path Path to the directory that contains
     * the model weights saved as txt files.
     * @param layer_names The names of the layers, which
     * should correspond to the file names on disk.
     */

    for (const auto& name: names) {

        if (std::strstr(name.c_str(), "dense")) {

            std::cout << "Loading layer: " << name << "\n";

            Mat<float> bias(0, 0);
            Mat<float> weights(0, 0);

            read_txt_data_to_matrix<bias_txt_suffix>(model_path, name, bias);
            read_txt_data_to_matrix<weights_txt_suffix>(model_path, name, weights);
            layers_.push_back(new Dense(name, weights, bias));
        } else if (std::strstr(name.c_str(), "sigmoid")) {
            std::cout << "Loading layer: " << name << "\n";
            layers_.push_back(new Sigmoid(name));
        } else {
            throw std::invalid_argument("Module constructor received invalid layer name");
        }
    }
}

Mat<float> Module::forward(const Mat<float>& input) const
{
    /**
     *
     * Run forward feed on all layers
     *
     * @param input The input tensor.
     * @return The resulting tensor after running
     * forward feeding on all existing layers.
     */

    if (layers_.empty()) {
        throw std::runtime_error("Module instance layers "
                                 "variable has not been "
                                 "initialized.");
    }

    Mat<float> value = input;
    for (const auto layer : layers_) {
        std::cout << "layer name: " << layer->name() << "\n";
        value = layer->forward(value);
    }
    return value;
}

Module::~Module()
{
    for (auto layer: layers_) {
        delete layer;
    }
}
