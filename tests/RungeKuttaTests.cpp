#include <gtest/gtest.h>
#include "../src/RK4.hpp"
#include "../src/DPRK4.hpp"
#include <fstream>
#include <string>
#include <random>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";
/*
TEST(RungeKuttaTests, firstFunctionTest){
    double endTime = 5.;
    double step = endTime/100;
    auto result = integrate<RK4Table, firstTask>(firstTask::StateAndArg{firstTask::State {0.}, 0}, endTime, step, firstTask{});
    ASSERT_NEAR(156.25,result.state(0),1 );
}
*/

TEST(RungeKuttaTests, mainFirstFunctionTest){
    double endTime = 5.;
    std::ofstream errFile;
    errFile.open(py_path + "/RK4/err.txt");

    for(std::size_t i = 0; i <= 10; i++){
        double z = 1e5/std::pow(2, i);
        //double z = 5;
        auto result = integrate<RK4Table, firstTask>(firstTask::StateAndArg{firstTask::State {0.}, 0},
                                                     endTime, endTime/z, firstTask{}, errFile);

        ASSERT_NEAR(156.25,result.state(0),0.1 );
        ASSERT_NEAR(5,result.arg,0.1 );
    }
}

TEST(RungeKuttaTests, mainSecondTest){
    double endTime = 5.;
    std::ofstream errFile;
    errFile.open(py_path + "/RK4/err2.txt");

    for(std::size_t i = 0; i <= 10; i++){
        double z = 1e5/std::pow(2, i);
        auto result = integrate<RK4Table, secondTask>(secondTask::StateAndArg{secondTask::State {0., 1.}, 0.},
                                                     endTime, endTime/z, secondTask{}, errFile);
        ASSERT_NEAR(std::sin(5),result.state(0), 1)<<result.state(0)<<" "<<result.state(1)<<"\n";
        ASSERT_NEAR(5,result.arg,0.1 );
    }
}
TEST(RungeKuttaTests, mainDPRKTest){
    std::ofstream errFile;
    errFile.open(py_path + "/RK4/errDP.txt");
    StepControl sc{};
    sc.minStep = 1e-4;
    sc.maxStep = 1;
    sc.initialStep = 0.01;
    sc.tolerance =1e-5;
    double endTime = 100. * 17.06521656;
    orbitAhrenstorf::StateAndArg initialState = {{0.994, 0, 0, -2.001585106}, 0.};
    auto result = integrate<DP45, orbitAhrenstorf>(initialState, endTime, sc, orbitAhrenstorf{});
    for(auto& it:result){
        errFile<<it.state(0)<< " "<<it.state(2)<<"\n";
    }
}

