#include <gtest/gtest.h>
#include "../src/Interpolant.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";

template<typename xType, uint32_t N>
std::array<xType, N> chebNulls(xType a, xType b){
    std::array<xType, N> answ{};
    for(uint32_t i = 0; i < N; i++){
        answ[i] = (b + a)/xType(2) + (b - a) * std::cos(M_PI*(2*i+1)/(2*N)) / xType(2);
    }
    return answ;
}


TEST(InterpolantTests, firstSimpleTest){
    constexpr uint32_t N = 4;
    double x = 2. / N;
    std::array<double, N> points{};
    std::array<double, N> values{1};
    for(uint32_t i = 0; i + 1 < N; i++){
        points[i + 1] = x * (i + 1);
        values[i + 1] = std::exp(points[i + 1]);
    }
    NewtonInterpolator<double, double, N> interpolator(points, values);
    std::array<double, N> answValue = interpolator.getSplitDifArrs();
    ASSERT_NEAR(answValue[0], 1., 0.1);
    ASSERT_NEAR(answValue[1], 1.297, 0.001);
    ASSERT_NEAR(answValue[2], 0.8416, 0.001);
    ASSERT_NEAR(answValue[3], 0.36, 0.01);
}


TEST(InterpolantTests, baseTest){
    std::ofstream fileOutBaseN3;
    std::ofstream fileOutBaseN4;
    std::ofstream fileOutBaseN5;
    fileOutBaseN3.open(py_path + "/Interpolant/errBaseN3.txt");
    fileOutBaseN4.open(py_path + "/Interpolant/errBaseN4.txt");
    fileOutBaseN5.open(py_path + "/Interpolant/errBaseN5.txt");
    double x = 2;
    double nulik = 0;
    int length = 20;
    std::array<double, 3> pointsN3{};
    std::array<double, 3> valuesN3{};
    std::array<double, 4> pointsN4{};
    std::array<double, 4> valuesN4{};
    std::array<double, 5> pointsN5{};
    std::array<double, 5> valuesN5{};
    std::array<double, 1000> valuesErr{};
    std::array<double, 1000> pointsErr{};
    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 3;
        double step_err = x_i / 999.;
        for(int j = 0; j < 3; j++){
            pointsN3[j] = j * step_i;
            valuesN3[j] = std::exp(pointsN3[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3);

        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN3<<err<<"\n";
    }


    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 4;
        double step_err = x_i / 999.;
        for(int j = 0; j < 4; j++){
            pointsN4[j] = j * step_i;
            valuesN4[j] = std::exp(pointsN4[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 4> interpolator(pointsN4, valuesN4);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN4<<err<<"\n";
    }


    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 5;
        double step_err = x_i / 999.;
        for(int j = 0; j < 5; j++){
            pointsN5[j] = j * step_i;
            valuesN5[j] = std::exp(pointsN5[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 5> interpolator(pointsN5, valuesN5);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN5<<err<<"\n";

    }

}

TEST(InterpolantTests, baseChebTest){
    std::ofstream fileOutBaseN3;
    std::ofstream fileOutBaseN4;
    std::ofstream fileOutBaseN5;
    fileOutBaseN3.open(py_path + "/Interpolant/errChebBaseN3.txt");
    fileOutBaseN4.open(py_path + "/Interpolant/errChebBaseN4.txt");
    fileOutBaseN5.open(py_path + "/Interpolant/errChebBaseN5.txt");
    double x = 2;
    double nulik = 0;
    int length = 20;
    std::array<double, 3> pointsN3{};
    std::array<double, 3> valuesN3{};
    std::array<double, 4> pointsN4{};
    std::array<double, 4> valuesN4{};
    std::array<double, 5> pointsN5{};
    std::array<double, 5> valuesN5{};
    std::array<double, 1000> pointsErr{};

    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        pointsN3 = chebNulls<double, 3>(double(0), x_i);
        double step_err = x_i / 999.;
        for(int j = 0; j < 3; j++){
            valuesN3[j] = std::exp(pointsN3[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN3<<err<<"\n";
    }

    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        pointsN4 = chebNulls<double, 4>(double(0), x_i);
        double step_err = x_i / 999.;
        for(int j = 0; j < 4; j++){
            valuesN4[j] = std::exp(pointsN4[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 4> interpolator(pointsN4, valuesN4);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN4<<err<<"\n";
    }


    for(int i = 0; i < length; i++){
        double err = 0;
        double x_i = x / std::pow(x, i);
        pointsN5 = chebNulls<double, 5>(double(0), x_i);
        double step_err = x_i / 999.;
        for(int j = 0; j < 5; j++){
            valuesN5[j] = std::exp(pointsN5[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 5> interpolator(pointsN5, valuesN5);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
        }
        fileOutBaseN5<<err<<"\n";
    }
}

TEST(InterpolantTests, baseSecondTest){
    std::ofstream fileOutBaseN3;
    std::ofstream fileOutBaseN4;
    std::ofstream fileOutBaseN5;
    std::ofstream fileOutBaseArgsN5;
    fileOutBaseN3.open(py_path + "/Interpolant/errSecondBaseN3.txt");
    fileOutBaseN4.open(py_path + "/Interpolant/errSecondBaseN4.txt");
    fileOutBaseN5.open(py_path + "/Interpolant/errSecondBaseN5.txt");
    fileOutBaseArgsN5.open(py_path + "/Interpolant/errArgsBaseN5.txt");
    double x = 2;
    double nulik = 0;
    std::array<double, 3> pointsN3{};
    std::array<double, 3> valuesN3{};
    std::array<double, 4> pointsN4{};
    std::array<double, 4> valuesN4{};
    std::array<double, 5> pointsN5{};
    std::array<double, 5> valuesN5{};
    std::array<double, 1000> valuesErr{};
    std::array<double, 1000> pointsErr{};
    for(int i = 0; i < 6; i++){
        double err = 0;
        double maxVal = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 4;
        double step_err = x_i / 999.;
        for(int j = 0; j < 3; j++){
            pointsN3[j] = (j + 1) * step_i;
            valuesN3[j] = std::exp(pointsN3[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
            maxVal = std::max(std::exp(pointsErr[j]), maxVal);
        }
        fileOutBaseN3<<err<<" "<< step_i<<" " << maxVal<<"\n";
    }


    for(int i = 0; i < 6; i++){
        double err = 0;
        double maxVal = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 5;
        double step_err = x_i / 999.;
        for(int j = 0; j < 4; j++){
            pointsN4[j] = (j + 1) * step_i;
            valuesN4[j] = std::exp(pointsN4[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 4> interpolator(pointsN4, valuesN4);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
            maxVal = std::max(std::exp(pointsErr[j]), maxVal);

        }
        fileOutBaseN4<<err<<" "<< step_i<<" " << maxVal<<"\n";
    }


    for(int i = 0; i < 6; i++){
        double err = 0;
        double maxVal = 0;
        double x_i = x / std::pow(x, i);
        double step_i = x_i / 6;
        double step_err = x_i / 999.;
        for(int j = 0; j < 5; j++){
            pointsN5[j] = (j + 1) * step_i;
            valuesN5[j] = std::exp(pointsN5[j]);
        }
        for(int j = 0; j < 1000; j++){
            pointsErr[j] = j * step_err;
        }

        NewtonInterpolator<double, double, 5> interpolator(pointsN5, valuesN5);
        for(int j = 0; j < 1000; j++){
            double interpV = interpolator.interpolate(pointsErr[j]);
            err = std::max(std::abs(std::exp(pointsErr[j]) - interpV), err);
            maxVal = std::max(std::exp(pointsErr[j]), maxVal);

        }
        fileOutBaseN5<<err<<" "<< step_i<<" " << maxVal<<"\n";
    }

}

TEST(InterpolantTests, classTest){
    std::array<double, 3> pointsN3{0, 1, 2};
    std::array<double, 3> valuesN3{1, 3, 9};
    NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3);
    std::array<double, 3> answ = interpolator.getSplitDifArrs();
    for(auto&& it: answ) std::cout<<it<<" ";
}
TEST(InterpolantTests, classChebTest){
    std::array<double, 3> pointsN4 = chebNulls<double, 3>(1, 2);
    /*std::array<double, 3> valuesN3{1, 3, 9};
    NewtonInterpolator<double, double, 3> interpolator(pointsN3, valuesN3);
    std::array<double, 3> answ = interpolator.getSplitDifArrs();*/
    for(auto&& it: pointsN4) std::cout<<it<<" ";
}