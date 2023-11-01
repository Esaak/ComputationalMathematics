#include <gtest/gtest.h>
#include "../src/SplineReal.hpp"
#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>


const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";
TEST(SplineTests, MainTest){
std::ofstream fileOut;
fileOut.open(py_path + "/SplineReal/err.txt");

std::array<double, 6> values5{};
std::array<double, 11> values10{};
std::array<double, 21> values20{};
std::array<double, 41> values40{};
std::array<double, 81> values80{};
std::array<double, 161> values160{};

std::array<double, 6> points5{};
std::array<double, 11> points10{};
std::array<double, 21> points20{};
std::array<double, 41> points40{};
std::array<double, 81> points80{};
std::array<double, 161> points160{};
constexpr std::array iter{5, 10, 20, 40, 80, 160};
double start = 0;
double end = 10;
auto func = [](auto& x){return std::exp(x);};
double dx = (end - start)/double(iter[0]);
for(std::size_t j = 0; j <= iter[0]; j++){
points5[j] = double(j) * dx;
values5[j] = std::exp(points5[j]);
}

dx = (end - start)/double(iter[1]);
for(std::size_t j = 0; j <= iter[1]; j++){
points10[j] = double(j) * dx;
values10[j] = std::exp(points10[j]);
}

dx = (end - start)/double(iter[2]);
for(std::size_t j = 0; j <= iter[2]; j++){
points20[j] = double(j) * dx;
values20[j] = std::exp(points20[j]);
}

dx = (end - start)/double(iter[3]);
for(std::size_t j = 0; j <= iter[3]; j++){
points40[j] = double(j) * dx;
values40[j] = std::exp(points40[j]);
}

dx = (end - start)/double(iter[4]);
for(std::size_t j = 0; j <= iter[4]; j++){
points80[j] = double(j) * dx;
values80[j] = std::exp(points80[j]);
}

dx = (end - start)/double(iter[5]);
for(std::size_t j = 0; j <= iter[5]; j++){
points160[j] = double(j) * dx;
values160[j] = std::exp(points160[j]);
}
CubicSpline<double, double, 5> s5{points5, values5, func(start), func(end)};
CubicSpline<double, double, 10> s10{points10, values10, func(start), func(end)};
CubicSpline<double, double, 20> s20{points20, values20, func(start), func(end)};
CubicSpline<double, double, 40> s40{points40, values40, func(start), func(end)};
CubicSpline<double, double, 80> s80{points80, values80, func(start), func(end)};
CubicSpline<double, double, 160> s160{points160, values160, func(start), func(end)};

std::size_t N = 1000;
double maxx = -1.;
dx = (end - start)/double(N);
std::size_t it= 0;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s5.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s5.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}

fileOut<<maxx<<"\n";

maxx = -1.;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s10.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s10.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}

fileOut<<maxx<<"\n";

maxx = -1.;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s20.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s20.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}

fileOut<<maxx<<"\n";

maxx = -1.;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s40.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s40.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}


fileOut<<maxx<<"\n";

maxx = -1.;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s80.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s80.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}


fileOut<<maxx<<"\n";

maxx = -1.;
for(std::size_t i = 0; i <= N; i++){
if(std::abs(s160.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
maxx = std::abs(s160.interpolate(dx * double(i))- std::exp(dx * double(i)));
it = i;
}
}


fileOut<<maxx<<"\n";
fileOut.close();
}
TEST(SplineTests, MainZeroTest){
    std::ofstream fileOut;
    fileOut.open(py_path + "/SplineReal/err_zero.txt");

    std::array<double, 6> values5{};
    std::array<double, 11> values10{};
    std::array<double, 21> values20{};
    std::array<double, 41> values40{};
    std::array<double, 81> values80{};
    std::array<double, 161> values160{};

    std::array<double, 6> points5{};
    std::array<double, 11> points10{};
    std::array<double, 21> points20{};
    std::array<double, 41> points40{};
    std::array<double, 81> points80{};
    std::array<double, 161> points160{};
    constexpr std::array iter{5, 10, 20, 40, 80, 160};
    double start = 0;
    double end = 10;
    auto func = [](auto& x){return std::exp(x);};
    double dx = (end - start)/double(iter[0]);
    for(std::size_t j = 0; j <= iter[0]; j++){
        points5[j] = double(j) * dx;
        values5[j] = std::exp(points5[j]);
    }

    dx = (end - start)/double(iter[1]);
    for(std::size_t j = 0; j <= iter[1]; j++){
        points10[j] = double(j) * dx;
        values10[j] = std::exp(points10[j]);
    }

    dx = (end - start)/double(iter[2]);
    for(std::size_t j = 0; j <= iter[2]; j++){
        points20[j] = double(j) * dx;
        values20[j] = std::exp(points20[j]);
    }

    dx = (end - start)/double(iter[3]);
    for(std::size_t j = 0; j <= iter[3]; j++){
        points40[j] = double(j) * dx;
        values40[j] = std::exp(points40[j]);
    }

    dx = (end - start)/double(iter[4]);
    for(std::size_t j = 0; j <= iter[4]; j++){
        points80[j] = double(j) * dx;
        values80[j] = std::exp(points80[j]);
    }

    dx = (end - start)/double(iter[5]);
    for(std::size_t j = 0; j <= iter[5]; j++){
        points160[j] = double(j) * dx;
        values160[j] = std::exp(points160[j]);
    }
    CubicSpline<double, double, 5> s5{points5, values5, 0, 0};
    CubicSpline<double, double, 10> s10{points10, values10, 0, 0};
    CubicSpline<double, double, 20> s20{points20, values20, 0, 0};
    CubicSpline<double, double, 40> s40{points40, values40, 0, 0};
    CubicSpline<double, double, 80> s80{points80, values80, 0, 0};
    CubicSpline<double, double, 160> s160{points160, values160, 0, 0};

    std::size_t N = 1000;
    double maxx = -1.;
    dx = (end - start)/double(N);
    std::size_t it= 0;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s5.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s5.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }

    fileOut<<maxx<<"\n";

    maxx = -1.;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s10.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s10.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }

    fileOut<<maxx<<"\n";

    maxx = -1.;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s20.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s20.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }

    fileOut<<maxx<<"\n";

    maxx = -1.;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s40.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s40.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }


    fileOut<<maxx<<"\n";

    maxx = -1.;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s80.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s80.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }


    fileOut<<maxx<<"\n";

    maxx = -1.;
    for(std::size_t i = 0; i <= N; i++){
        if(std::abs(s160.interpolate(dx * double(i))- std::exp(dx * double(i))) > maxx){
            maxx = std::abs(s160.interpolate(dx * double(i))- std::exp(dx * double(i)));
            it = i;
        }
    }


    fileOut<<maxx<<"\n";
    fileOut.close();
}