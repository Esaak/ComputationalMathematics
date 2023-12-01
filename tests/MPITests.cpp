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
    return x*x + tan(x) * tan(x) - 1.;
}
//double func1(double x){
//    return x - std::tan(std::sqrt(1-x*x));
//}
//double func2(double x){
//    return x - std::tan(-std::sqrt(1-x*x));
//}
std::vector<double> f(std::vector<double> v){
    v[0] = std::sqrt(-v[1]*v[1] + 1);
    v[1] = std::tan(v[0]);
    return v;
}

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
TEST(MPITests, vec_test){
    constexpr double x_init1 = 0.4;
    std::vector v_init= {+0.1, +0.1};
    constexpr double tol = 1e-6;
    constexpr double tau = 0.001;

    std::vector<double> answ_current = {0., 0.};
    std::vector<double> answ_next = v_init;
    std::size_t it = 2;

    //auto func = [](double x)->double {return x*x + tan(x)* tan(x) - 1;};
    auto euclid_norm = [](std::vector<double>& v1, std::vector<double>& v2){
        auto answ = 0.;
        for(std::size_t i = 0; i< v2.size(); i++){
            answ+=(v1[i] - v2[i]) * (v1[i] - v2[i]);
        }
        return std::sqrt(answ);
    };
    while(euclid_norm(answ_next, answ_current) > tol){
        answ_current = answ_next;
        answ_next = solve(f, tau, answ_current, it);

    }
    ASSERT_NEAR(euclid_norm(answ_next, answ_current), 0, tol);
    std::cout<<"x = "<<answ_next[0]<<", y = "<<answ_next[1]<<"\n";
    std::cout<<"x = "<< - answ_next[0]<<", y = "<< - answ_next[1]<<"\n";

}