//
// Created by Yongyang Nie on 4/1/22.
//

#ifndef FINAL_PROJECT_MODULE_H
#define FINAL_PROJECT_MODULE_H
#endif //FINAL_PROJECT_MODULE_H

#include <H5Cpp.h>
#include <iostream>
#include <vector>
#include <memory>
#include <ostream>


class Module {

public:
    template <const char *DataPath>
    static void read_1D_data(const std::string& path, std::vector<float>& out)
    {
        H5::H5File file(path.c_str(), H5F_ACC_RDONLY);
        H5::DataSet dataset = file.openDataSet(DataPath);
        H5::DataSpace dataspace = dataset.getSpace();

        out.resize(dataspace.getSimpleExtentNpoints());
        dataset.read(out.data(), H5::PredType::IEEE_F32LE);

        dataspace.close();
        dataset.close();
        file.close();
    }

    template <const char *DataPath>
    static void read_2D_data(const std::string& path, std::vector<std::vector<float>>& out)
    {
        H5::H5File file(path.c_str(), H5F_ACC_RDONLY);
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
};
