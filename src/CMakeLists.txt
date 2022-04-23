cmake_minimum_required(VERSION 3.21)
project(libNeuralNets VERSION 0.0.1) # DESCRIPTION A simple neural network library for mobile devices and embedded systems

set(CMAKE_CXX_STANDARD 20)

set(LIB_SRC_DIRS . layers module)
set(INCLUDE_DIR ../include)

find_package (Eigen3 3.3 REQUIRED)
find_package(h5cpp REQUIRED)

foreach(dir ${LIB_SRC_DIRS})
    file(GLOB LIB_HEADERS ${LIB_HEADERS} ${INCLUDE_DIR}/libNeuralNets/${dir}/*.h)
    file(GLOB LIB_SOURCES ${LIB_SOURCES} ${dir}/*.cpp)
endforeach()

include_directories(${LIB_SRC_DIRS} ${INCLUDE_DIR})

add_library(libNeuralNets ${LIB_HEADERS} ${LIB_SOURCES})
target_link_libraries(libNeuralNets Eigen3::Eigen h5cpp)
target_include_directories(libNeuralNets PRIVATE "/usr/local/include/" ${LIB_SRC_DIRS} ${INCLUDE_DIR})

add_executable(lib_test ../tests/test_libNeuralNets.cpp "/usr/local/bin/" ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(lib_test PRIVATE "/usr/local/include/" ${LIB_SRC_DIRS} ${INCLUDE_DIR})
target_link_libraries(lib_test Eigen3::Eigen h5cpp)
