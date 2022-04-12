module;

// importing <vector> seems to break module export, so we'll just include it
#include <vector>

import <string>;

export module LibNeuralNets;

export {
    class Module {
    public:
        Module(std::string filepath);

        const auto& bias0() { return bias0_; }
        const auto& kernel0() { return kernel0_; }

        const auto& bias1() { return bias1_; }
        const auto& kernel1() { return kernel1_; }

    private:
        std::vector<float> bias0_;
        std::vector<std::vector<float>> kernel0_;

        std::vector<float> bias1_;
        std::vector<std::vector<float>> kernel1_;
    };

    class Layer {

    public:
        virtual ~Layer();

    };

    class Conv2d {

    };

    class Dense {

    };

    class ReLU {

    };

    class Sigmoid {

    };
}
