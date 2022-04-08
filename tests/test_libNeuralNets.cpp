//
// Created by Yongyang Nie on 4/1/22.
//

#include <vector>
#include <index_notation/index_notation.h>
#include <tensor.h>
#include <format.h>
#include <iostream>
#include <stdexcept>


using namespace taco;

void try_taco() {

    // Create format
    Format csr({Dense, Dense});
    Format csf({Dense,Dense,Dense});
    Format sv({Dense});

    std::vector<float> v = {0, 1, 2, 3, 4};

    // Create tensors
    //    std::vector<>
    //    Tensor<float> tensor()
    Tensor<double> A({2,3}, 0);
    Tensor<double> B({2,3,4}, 0.0);
    Tensor<double> c({4}, 0);

    // Insert data into B and c
    B.insert({0,0,0}, 1.0);
    B.insert({1,2,0}, 2.0);
    B.insert({1,2,1}, 3.0);
    c.insert({0}, 4.0);
    c.insert({1}, 5.0);

    // Pack inserted data as described by the formats
    B.pack();
    c.pack();

    // Form a tensor-vector multiplication expression
    IndexVar i;
    IndexVar j;
    IndexVar k;
    A(i,j) = B(i,j,k) * c(k);

    // Compile the expression
    A.compile();

    // Assemble A's indices and numerically compute the result
    A.assemble();
    A.compute();

    std::cout << A << std::endl;
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
