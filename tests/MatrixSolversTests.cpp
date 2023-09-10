#include <gtest/gtest.h>
#include "../src/SlaeSolvers.hpp"

using namespace solvers;

TEST(SolversTests, GaussTest){
    std::vector<std::vector<double>> SimpleData{
            {1., 0., 0.},
            {0., 1., 0.},
            {0., 0., 1.}
    };
    std::vector<double>SimpleB{1., 1., 1.};
    Matrix SimpleMatrix(SimpleData);
    std::array<double, 3>SimpleAnsw = Gauss<double, 3>(SimpleMatrix, SimpleB);
    std::cout<<"Simple test: ";
    for(auto&& it:SimpleAnsw){
        std::cout<<it<<" ";
        ASSERT_EQ(it, 1.);
    }
    std::cout<<std::endl;

    std::vector<std::vector<double>> SecondData{
            {5., 8., -4.},
            {6., 9., -5.},
            {4., 7., -2.}
    };
    std::vector<double>SecondB{-18., -20., -15.};
    Matrix SecondMatrix(SecondData);
    std::array<double, 3>SecondAnsw = Gauss<double, 3>(SecondMatrix, SecondB);
    std::cout<<"Second test: ";
    for(auto&& it:SecondAnsw){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
}