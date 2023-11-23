#include <gtest/gtest.h>
#include "../src/MPI.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";


/**
 * Свернул систему:
 *  / x^2 + y^2 = 1
 *  \ y = tg(x)
 *  в два уравения:
 *  1.
 *      /x_i+1 = x_i + tau* (x_i^2 + tg^2(x_i) - 1)
 *      \x_0 = 1
 *  2.
 *      /x_i+1 = x_i + tau* (x_i^2 + tg^2(x_i) - 1)
 *      \x_0 = -1
 */

double func(double x){
    return x*x + tan(x)* tan(x) - 1.;
}
//double func1(double x){
//    return x - std::tan(std::sqrt(1-x*x));
//}
//double func2(double x){
//    return x - std::tan(-std::sqrt(1-x*x));
//}
TEST(MPITests, main_test){
    constexpr double x_init1 = 0.4;
    constexpr double tol = 1e-6;
    constexpr double tau = 0.1;

    double answ_current = 0;
    double answ_next = x_init1;
    std::size_t it = 2;

    //auto func = [](double x)->double {return x*x + tan(x)* tan(x) - 1;};

    while(std::abs(answ_current - answ_next) > tol){
        answ_current = answ_next;
        answ_next = solve(func, tau, answ_current, it);

    }
    ASSERT_NEAR(std::abs(answ_next - answ_current), 0, tol);
    std::cout<<"x = "<<answ_next<<", y = "<<std::tan(answ_next)<<"\n";
    std::cout<<"x = "<< - answ_next<<", y = "<< - std::tan(answ_next)<<"\n";

}