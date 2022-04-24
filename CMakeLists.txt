#set(CMAKE_CXX_COMPILER /usr/local/bin/g++-11)

cmake_minimum_required(VERSION 3.21)
project(libNeuralNets VERSION 0.0.1) # DESCRIPTION A simple neural network library for mobile devices and embedded systems

set(CMAKE_CXX_STANDARD 11)

find_package(HDF5 COMPONENTS CXX HL REQUIRED)
find_package (Eigen3 3.3 REQUIRED)
find_package(h5cpp REQUIRED)

#add_library(h5cpp SHARED "/usr/local/lib/" "/usr/local/include/h5cpp")
#set_target_properties(h5cpp PROPERTIES LINKER_LANGUAGE CXX)

find_library(H5CPP h5cpp)
if (NOT H5CPP)
    message(FATAL_ERROR "H5CPP not found")
endif()

link_directories()

add_executable(lib_test tests/test_libNeuralNets.cpp
        include/libNeuralNets/layers/Sigmoid.h
        include/libNeuralNets/layers/Dense.h
        include/libNeuralNets/layers/Layer.h
        include/libNeuralNets/module/Module.h
        src/layers/Sigmoid.cpp
        src/layers/Dense.cpp
        src/module/Module.cpp)
target_include_directories(lib_test PRIVATE "/usr/local/include" )
target_link_libraries(lib_test ${H5CPP} Eigen3::Eigen)
