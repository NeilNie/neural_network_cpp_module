//
// Created by Yongyang Nie on 4/1/22.
//

module;

#include <H5Cpp.h>

import <iostream>;
import <vector>;
import <string>;
import <memory>;
import <ostream>;

module LibNeuralNets;

static constexpr char bias0_path[] = "/model_weights/dense/dense/bias:0";
static constexpr char kernel0_path[] = "/model_weights/dense/dense/kernel:0";
static constexpr char bias1_path[] = "/model_weights/dense_1/dense_1/bias:0";
static constexpr char kernel1_path[] = "/model_weights/dense_1/dense_1/kernel:0";

template <const char *DataPath>
static void read_1D_data(const std::string& path, std::vector<float>& out)
{
    H5::H5File file(path, H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet(DataPath);
    H5::DataSpace dataspace = dataset.getSpace();

    out.resize(dataspace.getSimpleExtentNpoints());
    dataset.read(out.data(), H5::PredType::IEEE_F32LE);

    dataspace.close();
    dataset.close();
    file.close();
}

template <const char *DataPath>
static void read_2D_data(const std::string& path,
                         std::vector<std::vector<float>>& out)
{
    H5::H5File file(path, H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet(DataPath);
    H5::DataSpace dataspace = dataset.getSpace();

    hsize_t dims[dataspace.getSimpleExtentNdims()];
    dataspace.getSimpleExtentDims(dims);
    std::unique_ptr<float[]> data(new float[dims[0] * dims[1]]);
    dataset.read(data.get(), H5::PredType::IEEE_F32LE);

    dataspace.close();
    dataset.close();
    file.close();

    out.resize(dims[0]);
    for (size_t i = 0; i < out.size(); ++i)
        out[i].insert(out[i].end(),
                      data.get() + i*dims[1], data.get() + (i+1)*dims[1]);
}

Module::Module(std::string path)
{
    read_1D_data<bias0_path>(path, bias0_);
    read_2D_data<kernel0_path>(path, kernel0_);
    read_1D_data<bias1_path>(path, bias1_);
    read_2D_data<kernel1_path>(path, kernel1_);
}
