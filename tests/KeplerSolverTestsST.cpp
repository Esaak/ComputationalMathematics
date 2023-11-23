#include "../specific_tasks/keplerSolver.cpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <gtest/gtest.h>
const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";

TEST(KeplerTestsST, mainTest){
    std::ofstream fileOutBase_0_1;
    std::ofstream fileOutBase_0_2;
    std::ofstream fileOutBase_0_5;
    std::ofstream fileOutBase_0_8;
    fileOutBase_0_1.open(py_path + "/KeplerSolver/errBase_0_1.txt");
    fileOutBase_0_2.open(py_path + "/KeplerSolver/errBase_0_2.txt");
    fileOutBase_0_5.open(py_path + "/KeplerSolver/errBase_0_5.txt");
    fileOutBase_0_8.open(py_path + "/KeplerSolver/errBase_0_8.txt");

    constexpr double tol = 1e-5;
    constexpr double meanAnomaly = M_PI/4.;
    constexpr std::size_t maxIter = 1e6;

    double ecc = 0.1;

    auto first_out = [&fileOutBase_0_1](auto&& value) -> void {
        fileOutBase_0_1 << value<< '\n';
        return;
    };
    keplerSolver(ecc, meanAnomaly, maxIter, tol, first_out);



    ecc = 0.2;

    auto second_out = [&fileOutBase_0_2](auto&& value) -> void {
        fileOutBase_0_2 << value<< '\n';
        return;
    };


    keplerSolver(ecc, meanAnomaly, maxIter, tol, second_out);



    ecc = 0.5;

    auto third_out = [&fileOutBase_0_5](auto&& value) -> void {
        fileOutBase_0_5 << value<< '\n';
        return;
    };


    keplerSolver(ecc, meanAnomaly, maxIter, tol, third_out);


    ecc = 0.8;

    auto fourth_out = [&fileOutBase_0_8](auto&& value) -> void {
        fileOutBase_0_8 << value<< '\n';
        return;
    };


    keplerSolver(ecc, meanAnomaly, maxIter, tol, fourth_out);
}


