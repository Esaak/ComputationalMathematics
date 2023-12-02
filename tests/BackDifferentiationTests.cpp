#include <gtest/gtest.h>
#include "../src/BDF4.hpp"
#include "../src/RK4.hpp"
#include <fstream>
#include <string>
#include <random>

const std::string py_path = "/home/esaak/my_folder/CProjects/ComputationalMathematics/py";

TEST(BackDifferentiationTests, mainFirstFunctionTest){
    double endTime = 5.;
    std::ofstream errFile;
    errFile.open(py_path + "/BDF4/err.txt");
    auto func = [](auto x){return std::pow(x, 10)/10.;};
    double step = 0.01;
    IntegrationParameters parameters = {step, 1e-15, static_cast<size_t>(1e8)};
    for(std::size_t i = 0; i <= 10; i++){
        parameters.step += 1e-2;
        int stepNumber = endTime/parameters.step;
        std::vector<double> resultTrue;
        double r = 0;
        for(std::size_t j = 0; j <= stepNumber; j++){
            resultTrue.push_back(func(parameters.step * j));
        }
        resultTrue.push_back(func(endTime));
        auto result = integrate<BDF4, firstTask, RK4Table>(firstTask::StateAndArg{firstTask::State {0.}, 0},
                                                     endTime, parameters, firstTask{});
        for(std::size_t j = 0; j < result.size(); j++){
            //std::cout<<j<<" "<<result[j].state(0)<<" "<< resultTrue[j]<<"\n";
            r = std::max(r, std::abs((result[j].state(0) - resultTrue[j])));
        }
        errFile<<r<<"\n";
        EXPECT_NEAR(976562.5,result.back().state(0), 0.1 )<<result.back().state(0)<<"\n";
        ASSERT_NEAR(5,result.back().arg, 0.1);
    }
}

TEST(BackDifferentiationTests, mainSecondTest){
    double endTime = 5.;
    std::ofstream errFile;
    errFile.open(py_path + "/BDF4/err2.txt");
    auto func = [](auto x){return std::sin(x);};
    double step = 0.01;
    IntegrationParameters parameters = {step, 1e-15, static_cast<size_t>(1e6)};
    for(std::size_t i = 0; i <= 10; i++) {
        parameters.step += 0.01;
        int stepNumber = endTime / parameters.step;
        std::vector<double> resultTrue;
        double r = 0;
        for (std::size_t j = 0; j <= stepNumber; j++) {
            resultTrue.push_back(func(parameters.step * j));
        }

        resultTrue.push_back(func(endTime));

        auto result = integrate<BDF4, secondTask, RK4Table>(secondTask::StateAndArg{secondTask::State{0., 1.}, 0.},
                                                      endTime, parameters, secondTask{});

        for (std::size_t j = 0; j < result.size(); j++) {
            //std::cout<<j<<" "<<result[j].state(0) <<" "<< resultTrue[j]<<"\n";
            r = std::max(r, std::abs((result[j].state(0) - resultTrue[j])));
        }
        errFile << r << "\n";
        ASSERT_NEAR(std::sin(5.), result.back().state(0), 0.1) << result.back().state(0) << "\n";
        ASSERT_NEAR(5, result.back().arg, 0.1);
    }
}