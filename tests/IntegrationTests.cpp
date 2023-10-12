#include <gtest/gtest.h>
#include "../src/Integration.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";

template<std::floating_point T>
T foo(T x){
    return std::sqrt(x+1);
}

TEST(IntegrationTests, firstTest){
    std::ofstream fileOut3;
    std::ofstream fileOut5;
    fileOut3.open(py_path + "/Integration/errN3.txt");
    fileOut5.open(py_path + "/Integration/errN5.txt");
    constexpr double start = 0;
    constexpr double end = 10;
    constexpr std::array dx{8., 4., 2., 1., 1./2., 1./4., 1./8., 1./16., 1./32., 1./64., 1./128., 1./256., 1./512., 1./1024., 1./2048., 1./4096., 1./8192., 1./16384.};
    double answ = 1. - std::cos(double(10.));
    for(auto&& it: dx){
        fileOut3<< std::abs(answ - integrate<double(double), double, 3>(std::sin, start, end, it))<<"\n";
    }
    for(auto&& it: dx){
        fileOut5<< std::abs(answ - integrate<double(double), double, 5>(std::sin, start, end, it))<<"\n";
    }
    fileOut3.close();
    fileOut5.close();

}