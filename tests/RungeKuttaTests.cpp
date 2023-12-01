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
    auto func = [](auto x){return std::pow(x, 10)/10.;};
    double step = 1e-3;
    for(std::size_t i = 0; i <= 10; i++){
        step+=1e-3;
        int stepNumber = endTime/step;
        std::vector<double> resultTrue;
        double r = 0;
        for(std::size_t j = 0; j <= stepNumber; j++){
            resultTrue.push_back(func(step * j));
        }
        resultTrue.push_back(func(endTime));
        auto result = integrate<RK4Table, firstTask>(firstTask::StateAndArg{firstTask::State {0.}, 0},
                                                     endTime, step, firstTask{});
        for(std::size_t j = 0; j < result.size(); j++){
            //std::cout<<j<<" "<<std::abs(result[j].state(0) - resultTrue[j])<<"\n";
            r = std::max(r, std::abs((result[j].state(0) - resultTrue[j])));
        }
        errFile<<r<<"\n";
        ASSERT_NEAR(976562.5,result.back().state(0),0.1 )<<result.back().state(0)<<"\n";
        ASSERT_NEAR(5,result.back().arg,0.1 );
    }
}

TEST(RungeKuttaTests, mainSecondTest){
    double endTime = 5.;
    std::ofstream errFile;
    errFile.open(py_path + "/RK4/err2.txt");
    auto func = [](auto x){return std::sin(x);};
    double step = 1e-3;
    for(std::size_t i = 0; i <= 10; i++){
        step+=1e-3;
        int stepNumber = endTime/step;
        std::vector<double> resultTrue;
        double r = 0;
        for(std::size_t j = 0; j <= stepNumber; j++){
            resultTrue.push_back(func(step * j));
        }

        resultTrue.push_back(func(endTime));

        auto result = integrate<RK4Table, secondTask>(secondTask::StateAndArg{secondTask::State {0., 1.}, 0.},
                                                      endTime, step, secondTask{});

        for(std::size_t j = 0; j < result.size(); j++){
            //std::cout<<j<<" "<<std::abs(result[j].state(0) - resultTrue[j])<<"\n";
            r = std::max(r, std::abs((result[j].state(0) - resultTrue[j])));
        }
        errFile<<r<<"\n";
        ASSERT_NEAR(std::sin(5.),result.back().state(0),0.1 )<<result.back().state(0)<<"\n";
        ASSERT_NEAR(5,result.back().arg,0.1 );
    }
}

TEST(RungeKuttaTests, mainDPRKTest){
    std::ofstream errFile;
    errFile.open(py_path + "/RK4/errDP.txt");
    StepControl sc{};
    sc.minStep = 1e-6;
    sc.maxStep = 1e-1;
    sc.initialStep = 1e-4;
    sc.tolerance =1e-5;
    double endTime = 17.06521656 * 2;
    orbitAhrenstorf::StateAndArg initialState = {{0.994, 0, 0, -2.001585106}, 0.};
    auto result = integrate<DP45, orbitAhrenstorf>(initialState, endTime, sc, orbitAhrenstorf{});
    for(auto& it:result){
        errFile<<it.state(0)<< " "<<it.state(2)<<"\n";
    }
}

