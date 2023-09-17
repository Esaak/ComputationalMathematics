#include <gtest/gtest.h>
#include "../src/SlaeSolvers.hpp"

using namespace solvers;

TEST(SolversTests, GaussTest){

    std::array<double, 3>SimpleB{1., 1., 1.};
    Matrix<double, 3> SimpleMatrix = {1., 0., 0.,
                           0., 1., 0.,
                           0., 0., 1.};
    std::array<double, 3>SimpleAnsw = Gauss<double, 3>(SimpleMatrix, SimpleB);
    std::cout<<"Simple test: ";
    for(auto&& it:SimpleAnsw){
        std::cout<<it<<" ";
        ASSERT_EQ(it, 1.);
    }
    std::cout<<std::endl;


    std::array<double, 3>SecondB{-18., -20., -15.};
    Matrix<double, 3> SecondMatrix = {5., 8., -4.,
    6., 9., -5.,
    4., 7., -2.};
    std::array<double, 3>SecondAnsw = Gauss<double, 3>(SecondMatrix, SecondB);
    std::cout<<"Second test: ";
    for(auto&& it:SecondAnsw){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
}

TEST(SolversTests, GaussDifTest){
    std::array<double, 4>b{1.2, 2.1, 1., 5.6};
    Matrix<double, 4> SimpleMatrix = {1.2, 4.4, 2., 6.,
                                      4., 11., 0., 87,
                                      3., 10., 9., 5.6,
                                      2.1, 1.1, 3., 1.3};
    std::array<double, 4>SimpleAnsw = Gauss<double, 4>(SimpleMatrix, b);
    std::cout<<"Simple test: ";
    for(auto&& it:SimpleAnsw){
        std::cout<<it<<" ";

    }
    std::cout<<std::endl;
}