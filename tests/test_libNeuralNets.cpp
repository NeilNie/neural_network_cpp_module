//
// Created by Yongyang Nie on 4/1/22.
//

import <iostream>;

import LibNeuralNets;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <h5>\n";
        return 1;
    }
    Module mod(argv[1]);
    std::cout << "dense bias: \n";
    for (auto val : mod.bias0())
        std::cout << val << '\n';
    std::cout << "\ndense kernel: \n";
    for (const auto& vec : mod.kernel0())
        for (auto val : vec)
            std::cout << val << '\n';
    std::cout << "\ndense_1 bias: \n";
    for (auto val : mod.bias1())
        std::cout << val << '\n';
    std::cout << "\ndense_1 kernel: \n";
    for (const auto& vec : mod.kernel1())
        for (auto val : vec)
            std::cout << val << '\n';
}
