//
// Created by Yongyang Nie on 4/1/22.
//

#include <stdexcept>
#include "../include/libNeuralNets/module/Module.h"

int main() {

    std::string path = "/Users/neilnie/model/";
    std::vector<std::string> layers{"dense_1", "sigmoid_1", "dense_2", "sigmoid_2", "dense_3"};

    Module neural_net = Module(path, layers);
}

void test_mat_mult() {

    nn::Mat<float> a(2, 3, 0);
    nn::Mat<float> b(3, 2, 0);

    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 1) = 5;
    a(1, 2) = 4;

    b(0, 0) = 1;
    b(0, 1) = 2;
    b(1, 1) = 1;

    std::cout << a * b << std::endl;

}