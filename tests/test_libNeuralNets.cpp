//
// Created by Yongyang Nie on 4/1/22.
//

#include <vector>
#include <tensor.h>
#include <iostream>
#include <stdexcept>


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
}
