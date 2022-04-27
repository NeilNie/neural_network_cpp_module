//
// Created by Yongyang Nie on 4/1/22.
//

module;

// importing <vector> seems to breaks things on certain platforms
#include <vector>

import <iostream>;
import <string>;
import <stdexcept>;
import <system_error>;
import <memory>;
import <cstring>;
import <cstdio>;
import <cstdlib>;

module LibNeuralNets;

using namespace nn;

template <const char *DataPathSuffix, bool Verbose = true>
static void read_txt_data_to_matrix(const std::string& path,
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

    if constexpr (Verbose)
        std::cout << "loading from file: " << full_path.get() << "\n";

    // using C stdio instead of std::fstream because the later seems to incur
    // internal compiler error in a module
    FILE *file = std::fopen(full_path.get(), "r");
    if (file == nullptr)
        throw std::system_error(errno, std::generic_category());
    int count = 0;

    int rows, cols;
    std::vector<float> data;
    char *line = nullptr;
    size_t n = 0;
    while (::getline(&line, &n, file) != -1) {
        float line_data = std::strtof(line, nullptr);
        if (count == 0) {
            rows = (int) line_data;
        } else if (count == 1) {
            cols = (int) line_data;
        } else {
            data.push_back(line_data);
        }
        count++;
    }
    std::free(line);
    bool ferr = std::ferror(file);
    std::fclose(file);
    if (ferr)
        throw std::system_error(errno, std::generic_category());

    if constexpr (Verbose)
        std::cout << "matrix rows: " << rows << " columns: " << cols << "\n";

    out.resize(rows, cols);

    for (auto i = 0; i < out.n_rows(); i++)
        for (auto j = 0; j < out.n_cols(); j++)
            out(i, j) = data[i * out.n_cols() + j]; //

    if constexpr (Verbose)
        std::cout << "Finished loading" << "\n";
}

static constexpr char bias_txt_suffix[] = "_bias.txt";
static constexpr char weights_txt_suffix[] = "_weights.txt";

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
    std::cout << value << "\n";
    return value;
}

Module::~Module()
{
    for (auto layer: layers_) {
        delete layer;
    }
}
