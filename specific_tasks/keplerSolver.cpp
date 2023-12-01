#include <stdexcept>
#include <cmath>
#include <iostream>
/**
    Решает уравнение Кеплера методом Ньютона
    * ecc - эксцентриситет, принадлежит (0, 1)
    * meanAnomaly - средняя аномалия, М (радианы)
    * maxIter - максимальное количество итераций
    * tol - точность, с которой нужно отыскать решение
**/
double keplerSolver(double ecc, double meanAnomaly, unsigned int maxIter, double tol, auto& out_func = nullptr){
    double answer_current = 0.;
    double answer_next = meanAnomaly;
    auto func = [&meanAnomaly, &ecc](auto&& E){return E + ecc*std::sin(E) - meanAnomaly;};
    auto dfunc = [&ecc](auto&& E){return 1 + ecc*std::cos(E);};
    for(auto i = 0; i < maxIter; i++){
        answer_current = answer_next;
        answer_next = answer_current - func(answer_current)/dfunc(answer_current);

        out_func(std::abs(answer_current - answer_next));

        if(std::abs(answer_current - answer_next) < tol){
            return answer_next;
        }
    }
    throw std::invalid_argument( "iterations more than maxIter" );
}
