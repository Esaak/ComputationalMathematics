#include <gtest/gtest.h>
#include "../src/NumDiff.hpp"
#include <fstream>
#include <string>
#include <random>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";
TEST(NumDiffTests, FirstBaseTest){
    constexpr std::uint64_t N = 2;
    std::array<double, N> points = {-1, 1};
    DerivativeCoef<double, N> answ = calcDerivativeCoef(points);
    ASSERT_EQ(answ.centralCoef, 0);
    std::cout<<answ.centralCoef<<"\n";
    ASSERT_EQ(answ.otherCoefs[0], -0.5);
    ASSERT_EQ(answ.otherCoefs[1], 0.5);
}

TEST(NumDiffTests, SecondBaseTest){
    std::uint64_t N = 2;
    std::array<double, 2> points = {1, 2};
    DerivativeCoef<double, 2> answ = calcDerivativeCoef(points);
    ASSERT_EQ(answ.centralCoef, -1.5);
    std::cout<<answ.centralCoef<<"\n";
    ASSERT_EQ(answ.otherCoefs[0], 2);
    ASSERT_EQ(answ.otherCoefs[1], -0.5);
}

TEST(NumDiffTests, mainBaseTest){
    std::ofstream fileOut;
    fileOut.open(py_path + "/NumDiff/errSecond.txt");
    constexpr double x = 1.;
    constexpr std::uint64_t N3 = 3;
    constexpr std::uint64_t N4 = 4;
    constexpr std::uint64_t N5 = 5;
    std::array<double, N3> pointsN3={1., 2., 3.};
    std::array<double, N4> pointsN4={1., 2., 3., 4.};
    std::array<double, N5> pointsN5={1., 2., 3., 4., 5.};
    std::array<double, 16> h{};
    h[0]=1;
    for(std::uint64_t i =0; i + 1 < h.size(); i++) {
        h[i + 1] = h[i] * 0.1;
    }

    DerivativeCoef<double, N3> answN3 = calcDerivativeCoef(pointsN3);
    double DN3 = answN3.centralCoef * std::exp(x);
    std::cout<< std::exp(x);
    for(auto&& it: answN3.otherCoefs) std::cout<< it<<" ";
    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN3.size(); j++){
            DN3+=answN3.otherCoefs[j] * std::exp(x + pointsN3[j]*it);
        }
        fileOut<<std::abs(DN3/it - std::exp(x))<<" ";
    }
    fileOut<<std::endl;

    DerivativeCoef<double, N4> answN4 = calcDerivativeCoef(pointsN4);
    double DN4 = answN4.centralCoef * std::exp(x);

    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN4.size(); j++){
            DN4+=answN4.otherCoefs[j] * std::exp(x + pointsN4[j]*it);
        }
        fileOut<<std::abs(double(DN4)/it - double(std::exp(x)))<<" ";
    }
    fileOut<<std::endl;

    DerivativeCoef<double, N5> answN5 = calcDerivativeCoef(pointsN5);
    double DN5 = answN5.centralCoef * std::exp(x);
    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN5.size(); j++){
            DN5+=answN5.otherCoefs[j] * std::exp(x + pointsN5[j]*it);
        }
        fileOut<<std::abs(DN5/it - std::exp(x))<<" ";
    }
    fileOut<<std::endl;
    fileOut.close();
}

TEST(NumDiffTests, FirstAdvancedTest){
    constexpr std::uint64_t N = 2;
    constexpr std::uint64_t L = 2;
    std::array<double, 2> points = {-1, 1};
    DerivativeCoef<double, N> answ = calcDerivativeCoef<double, N, L>(points);
    ASSERT_EQ(answ.centralCoef, -2.);
    std::cout<<answ.centralCoef<<"\n";
    ASSERT_EQ(answ.otherCoefs[0], 1.);
    ASSERT_EQ(answ.otherCoefs[1], 1);
}

TEST(NumDiffTests, mainAdvancedTest){
    std::ofstream fileOut;
    fileOut.open(py_path + "/NumDiff/errAdvanced.txt");
    constexpr double x = 1;
    constexpr std::uint64_t L = 2;
    constexpr std::uint64_t N3 = 3;
    constexpr std::uint64_t N4 = 4;
    constexpr std::uint64_t N5 = 5;
    std::array<double, N3> pointsN3={-1., 1., 2.};
    std::array<double, N4> pointsN4={-2., -1., 1., 2.};
    std::array<double, N5> pointsN5={-2., -1., 1., 2., 3.};
    std::array<double, 16> h{};
    h[0]=1;
    for(std::uint64_t i =0; i + 1 < h.size(); i++) {
        h[i + 1] = h[i] * 0.1;
    }

    DerivativeCoef<double, N3> answN3 = calcDerivativeCoef<double, N3, L>(pointsN3);
    double DN3 = answN3.centralCoef * std::exp(x);
    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN3.size(); j++){
            DN3+=answN3.otherCoefs[j] * std::exp(x + pointsN3[j]*it);
        }
        fileOut<<std::abs(DN3/std::pow(it, L) - std::exp(x))<<" ";
    }
    fileOut<<std::endl;

    DerivativeCoef<double, N4> answN4 = calcDerivativeCoef<double, N4, L>(pointsN4);
    double DN4 = answN4.centralCoef * std::exp(x);
    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN4.size(); j++){
            DN4+=answN4.otherCoefs[j] * std::exp(x + pointsN4[j]*it);
        }
        fileOut<<std::abs(DN4/std::pow(it, L) - std::exp(x))<<" ";
    }
    fileOut<<std::endl;

    DerivativeCoef<double, N5> answN5 = calcDerivativeCoef<double, N5, L>(pointsN5);
    double DN5 = answN5.centralCoef * std::exp(x);
    for(auto&& it : h){
        for(std::uint64_t j = 0; j < pointsN5.size(); j++){
            DN5+=answN5.otherCoefs[j] * std::exp(x + pointsN5[j]*it);
        }
        fileOut<<std::abs(DN5/std::pow(it, L) - std::exp(x))<<" ";
    }
    fileOut<<std::endl;
    fileOut.close();
}