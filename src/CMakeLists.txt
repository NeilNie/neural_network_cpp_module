cmake_minimum_required(VERSION 3.21)
project(libNeuralNets)

set(CMAKE_CXX_STANDARD 20)

set(LIB_SRC_DIRS . layers module)
set(INCLUDE_DIR ../include)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${LIB_SRC_DIRS} ${INCLUDE_DIR} /usr/local/include/taco)

add_executable(lib_test ../tests/test_libNeuralNets.cpp "/usr/local/bin/" ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(lib_test PRIVATE "/usr/local/include/" ${LIB_SRC_DIRS} ${INCLUDE_DIR})
target_link_libraries(lib_test "/usr/local/bin/" Eigen3::Eigen)
