#include <gtest/gtest.h>
#include "../src/IntegrationRunge.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";

template<std::floating_point T>
T foo(T x){
    return std::sqrt(x+1);
}
template<std::floating_point T>
T func1(T start, T end, auto& func){
    return (end - start) * (func(start) + 4 * func((start + end)/2.) + func(end))/6.;
}
TEST(IntegrationRungeTests, assertTest){
    constexpr double start = 0;
    constexpr double end = 10;
    constexpr double it = 1;
    constexpr double acc = 0;
    std::size_t p = 4;
    fc<double, double(double), func1<double>> cf;
    cf.p = p;
    std::cout<< integrateRunge<double(double)>(std::sin, cf, start, end, it, acc)<<"\n";

}


TEST(IntegrationRungeTests, firstTest){
    std::ofstream fileOut3;
    fileOut3.open(py_path + "/IntegrationRunge/errN3.txt");
    //fileOut5.open(py_path + "/IntegrationSimpson/errN5.txt");
    constexpr double start = 0;
    constexpr double end = 10;
    constexpr int N = 30;
    //constexpr std::array dx{1., 1./2., 1./4., 1./8., 1./16., 1./32., 1./64., 1./128., 1./256., 1./512., 1./1024.,
    //                        1./2048., 1./4096., 1./8192., 1./16384., 1./32768., 1./65636.};
    std::vector<double> dx(N);
    dx[0] = 1.;
    for(std::size_t i = 1; i < N; i++){
        dx[i] = dx[i-1]/2.;
    }
    double answ = 1. - std::cos(double(10.));
    std::size_t p = 4;
    fc<double, double(double), func1<double>> cf;
    cf.p = p;
    for(auto&& it: dx){
        auto real_answ = integrateRunge<double(double)>(std::sin, cf, start, end, it, 0);
        fileOut3<< std::abs(std::abs(answ - real_answ) - it)<<"\n";
    }

    fileOut3.close();

}