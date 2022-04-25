//
// Created by Yongyang Nie on 4/1/22.
//

#include <stdexcept>
#include "../include/libNeuralNets/module/Module.h"

int main() {

    std::cout << "hello world" << std::endl;

    std::string path = "/Users/neilnie/model/";
    std::vector<std::string> layers{"dense_1", "sigmoid_1", "dense_2", "sigmoid_2", "dense_3"};

    Module neural_net = Module(path, layers);
}
