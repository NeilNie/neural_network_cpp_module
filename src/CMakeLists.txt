cmake_minimum_required(VERSION 3.21)
project(libNeuralNets)

set(CMAKE_CXX_STANDARD 20)

set(LIB_SRC_DIRS . layers module)
set(INCLUDE_DIR ../include)

find_library(LIB_TACO PATHS)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

foreach(dir ${LIB_SRC_DIRS})
    file(GLOB LIB_HEADERS ${LIB_HEADERS} ${INCLUDE_DIR}/libNeuralNets/${dir}/*.h)
    file(GLOB LIB_SOURCES ${LIB_SOURCES} ${dir}/*.cpp)
endforeach()

include_directories(${LIB_SRC_DIRS} ${INCLUDE_DIR} /usr/local/include/taco)

#add_library(libNeuralNets ${STATIC} ${LIB_HEADERS} ${LIB_SOURCES})

add_executable(lib_test ../tests/test_libNeuralNets.cpp "/usr/local/bin/" ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(lib_test PRIVATE "/usr/local/include/" ${LIB_SRC_DIRS} ${INCLUDE_DIR})
target_link_libraries(lib_test "/usr/local/bin/" Eigen3::Eigen)
