#pragma once

#include <array>
#include <vector>
#include <Eigen/Eigen>
#include <span>

struct IntegrationParameters{
    double step;  // шаг интегрирования
    double epsilon;  // точность решения нелинейного уравнения
    std::size_t maxIter;  // максимальное количество итераций для решения нелинейного уравнения
};

/***
BDF - структура с коэффициентами метода
RHS - правая часть Д.У.
RKTable -  таблица Бутчера метода Рунге-Кутты для разгона.
***/

template<typename BDF, typename RHS, typename RKTable>  // таблица бутчера и класс правой части f
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg& initialState,
        const typename RHS::Argument& endTime,
        const IntegrationParameters& parameters,
        const RHS& rhs
);

/*______________________Realization_________________________________*/

template<typename T>

concept IsContainer = requires(T t) {

    typename T::value_type;

    {t.begin()} -> std::same_as<typename T::iterator>;

    {t.end()} -> std::same_as<typename T::iterator>;

};

template<typename T>
T abs(T value){
    return std::abs(value);
}
template<IsContainer T>
T::value_type abs(T value){
    return std::abs(value(0));
}
template<typename v1Type,typename v2Type, std::size_t N>
v2Type v2v(const std::array<v1Type, N> &v1, const std::array<v2Type, N> &v2) {
    if (v2.empty() or v1.empty()) throw std::invalid_argument("bad arguments");
    v2Type result = v1[0] * v2[0];
    for (std::size_t i = 1; i < v2.size(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}


template<typename rType,typename uType, typename fType>
uType MPI4BDF(auto& func,
              const uType& initialGuess,
              const IntegrationParameters& parameters,
              rType step
              ){
    fType uCurrent= initialGuess.state - initialGuess.state;
    fType uNext = initialGuess.state;
    for(std::size_t i = 0;
        i < parameters.maxIter and abs<fType>(uNext - uCurrent) > parameters.epsilon;
        i++){
        uCurrent = uNext;
        uNext = func({uNext, step + initialGuess.arg}, step);
    }
    return {uNext, step + initialGuess.arg};
}

struct BDF4{
    static constexpr unsigned int size = 4;
    using rType = double;
    using vType = std::array<rType , size>;
    static constexpr vType alpha = {3./25., -16./25., 36./25., -48./25.};
    static constexpr rType fCoef = 12./25;
};
template<typename BDF, typename RHS, typename RKTable>
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg& initialState,
        const typename RHS::Argument& endTime,
        const IntegrationParameters& parameters,
        const RHS& rhs
){
    using utype = typename RHS::StateAndArg;
    using ftype = typename RHS::State;
    using rtype = typename RHS::Argument;
    std::size_t stepNum = endTime/parameters.step;
    if (stepNum < BDF::size - 1) throw std::invalid_argument("sooo big step");
    std::vector<utype> uVector = integrate<RKTable, RHS>(initialState,parameters.step * (BDF::size - 1), parameters.step, rhs);
    uVector.reserve(stepNum + 1);
    auto func = [&parameters, &rhs, &uVector](utype && x, rtype step) -> ftype{
        std::array<ftype, BDF::size> range;
        std::transform(uVector.end() - BDF::size, uVector.end(), range.begin(), [](auto& x){return x.state;});
        auto fTypeScalar = v2v<typename BDF::rType, ftype, BDF::size>(BDF::alpha, range);
        return step * rhs.calc(x) * BDF::fCoef - fTypeScalar;
    };
    for(std::size_t i = BDF::size; i <= stepNum; i++) {
        uVector.push_back(MPI4BDF<rtype, utype, ftype>(func, uVector.back(), parameters, parameters.step));
    }
    if(endTime - stepNum * parameters.step>0){
        uVector.push_back(integrate<RKTable, RHS>(uVector.back(),endTime - stepNum * parameters.step,
                                                  endTime - stepNum * parameters.step, rhs).back());
    }
    return uVector;
}