//
// Created by Yongyang Nie on 4/1/22.
//

#include <stdexcept>
#include "../include/libNeuralNets/module/Module.h"

int main() {

    std::string path = "/Users/neilnie/model/";
    std::vector<std::string> layers{"dense_1", "sigmoid_1", "dense_2", "sigmoid_2", "dense_3"};

    nn::Mat<float> input(784, 1, 0);
    Module neural_net = Module(path, layers);

     std::cout << "Running forward feed..." << "\n";
     auto output = neural_net.forward(input);
     std::cout << "Finished" << "\n";
}

void test_mat_mult_add() {

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

    nn::Mat<float> c(2, 3, 0);

    c(0, 0) = 1;
    c(0, 1) = 2;
    c(0, 2) = 3;
    c(1, 0) = 4;
    c(1, 1) = 5;
    c(1, 2) = 6;


    b(0, 0) = 10;
    b(0, 1) = 11;

    b(1, 0) = 20;
    b(1, 1) = 21;

    b(2, 0) = 30;
    b(2, 1) = 31;

    /* Expected
     * 140	146
     * 320	335
     *
     */
    std::cout << c * b << std::endl;

    std::cout << a << std::endl;
    std::cout << c << std::endl;

    /*
     * Expected:
     * 2	4	3
     * 4	10 10
     *
     */
    std::cout << a + c << std::endl;
}

/**
int main() {

    std::string path = "/Users/shannon/Documents/COMSW4995_final_project/data/model/";
    std::vector<std::string> layers{"dense_1", "sigmoid_1", "dense_2", "sigmoid_2", "dense_3"};

    Module neural_net = Module(path, layers);
}
*/

