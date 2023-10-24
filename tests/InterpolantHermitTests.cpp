#include <gtest/gtest.h>
#include "../src/InterpolantHermit.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";


TEST(InterpolantHermitTests, basicTest){
    std::array<double, 3> pointsN3{1, 2, 3};
    std::array<double, 3> valuesN3{-1, 0, 1};
    std::array<double, 3> derivN3{2, 3, 2};
    NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3, derivN3);
    std::array<double, 6> answ = interpolator.getSplitDifArrs();
    for(auto&& it: answ) std::cout<<it<<" ";

}

TEST(InterpolantTests, mainTest){
    std::ofstream fileOutBaseN3;
    std::ofstream fileOutBaseN4;
    std::ofstream fileOutBaseN5;
    fileOutBaseN3.open(py_path + "/InterpolantHermit/errBaseN3.txt");
    fileOutBaseN4.open(py_path + "/InterpolantHermit/errBaseN4.txt");
    fileOutBaseN5.open(py_path + "/InterpolantHermit/errBaseN5.txt");
    double x = 2;
    int length = 20;
    std::array<double, 3> pointsN3{};
    std::array<double, 3> valuesN3{};
    std::array<double, 3> derivN3{};
    std::array<double, 4> pointsN4{};
    std::array<double, 4> valuesN4{};
    std::array<double, 4> derivN4{};
    std::array<double, 5> pointsN5{};
    std::array<double, 5> valuesN5{};
    std::array<double, 5> derivN5{};
    std::array<double, 1000> valuesErr{};
    std::array<double, 1000> pointsErr{};
    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 2.;
        double step_err = x_i / 999.;
        for(int j = 0; j < 3; j++){
            pointsN3[j] = j * step_i;
            valuesN3[j] = std::exp(pointsN3[j]);
            derivN3[j] = std::exp(pointsN3[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3, derivN3);

        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN3<<err<<"\n";
    }


    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 3;
        double step_err = x_i / 999.;
        for(int j = 0; j < 4; j++){
            pointsN4[j] = j * step_i;
            valuesN4[j] = std::exp(pointsN4[j]);
            derivN4[j] = std::exp(pointsN4[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 4> interpolator(pointsN4, valuesN4, derivN4);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN4<<err<<"\n";
    }


    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 4;
        double step_err = x_i / 999.;
        for(int j = 0; j < 5; j++){
            pointsN5[j] = j * step_i;
            valuesN5[j] = std::exp(pointsN5[j]);
            derivN5[j] = std::exp(pointsN5[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 5> interpolator(pointsN5, valuesN5, derivN5);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN5<<err<<"\n";

    }

}