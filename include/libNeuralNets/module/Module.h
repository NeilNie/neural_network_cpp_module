//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_MODULE_H
#define FINAL_PROJECT_MODULE_H
#endif //FINAL_PROJECT_MODULE_H

#include <iostream>
#include <vector>
#include <memory>
#include <ostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "../layers/Layer.h"
#include "../layers/Dense.h"
#include "../layers/Sigmoid.h"


class Module {

public:

    // instance variables
    std::vector<std::string> layer_names;
    std::vector<Layer *> layers;
    explicit Module(const std::string& model_path, const std::vector<std::string>& names);
    explicit Module(std::vector<Layer> layers);
    ~Module();
    nn::Mat<float> forward(const nn::Mat<float>& input);

    static void read_txt_data_to_matrix(
            const std::string& path,
            const std::string& data_path,
            nn::Mat<float>& out,
            bool verbose=true) {

        if (verbose) {
            std::cout << "Begin loading..." << "\n";
        }

        if (verbose) {
            std::cout << "loading from file: " << path + data_path << "\n";
        }

        std::ifstream file(path + data_path);
        std::string str;
        int count = 0;

        int rows, cols;
        std::vector<float> data;
        while (std::getline(file, str)) {
            float line_data = std::strtof(str.c_str(), nullptr);
            if (count == 0) {
                rows = (int) line_data;
            } else if (count == 1) {
                cols = (int) line_data;
            } else {
                data.push_back(line_data);
            }
            count++;
        }

        if (verbose)
            std::cout << "matrix rows: " << rows << " columns: " << cols << "\n";

        out.resize(rows, cols);

        for (auto i = 0; i < out.n_rows(); i++)
            for (auto j = 0; j < out.n_cols(); j++)
                out(i, j) = data[i * out.n_cols() + j]; //

        if (verbose)
            std::cout << "Finished loading" << "\n";
    }
};

