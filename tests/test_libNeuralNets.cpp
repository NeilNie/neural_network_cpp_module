//
// Created by Yongyang Nie on 4/1/22.
//

#include <stdexcept>
#include "../include/libNeuralNets/module/Module.h"


static constexpr char bias0_path[] = "/model_weights/dense/dense/bias:0";
static constexpr char kernel0_path[] = "/model_weights/dense/dense/kernel:0";
static constexpr char bias1_path[] = "/model_weights/dense_1/dense_1/bias:0";
static constexpr char kernel1_path[] = "/model_weights/dense_1/dense_1/kernel:0";


int main() {

    std::cout << "hello world" << std::endl;

    std::string path = "/Users/neilnie/model/";
    std::vector<std::string> layers{"dense_1", "sigmoid_1", "dense_2", "sigmoid_2", "dense_3"};

    Module neural_net = Module(path, layers);
}









/*
using namespace taco;

void try_taco() {

}

Tensor<float> populate_matrix(std::vector<float>& input, int width, int height) {

    if (width * height != input.size())
        throw std::invalid_argument("Input data and width and height mismatch");

    Tensor<double> mat({height, width}, 0);
    for (auto i = 0; i < input.size(); i++) {
        mat.insert({i / height, i % width}, input[i]);
    }

    std::cout << mat << std::endl;

    return mat;
}

int main() {

    std::vector<float> input = {0, 1, 2, 3, 4, 5};
    auto a = populate_matrix(input, 3, 2);
    return 0;
} */
