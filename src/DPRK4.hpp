#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <Eigen/Eigen>

struct DP45{
    static constexpr unsigned int stages = 7;
    using vType = std::array<double, stages>;
    static constexpr std::array<vType , stages> table = {{{0., 0., 0., 0., 0., 0., 0.},
                                                                             {1./5., 0., 0., 0., 0., 0., 0.},
                                                                             {3./40., 9./40., 0., 0., 0., 0., 0.},
                                                                             {44./45., -56./15., 32./9.,0., 0., 0., 0.},
                                                                             {19372./6561., -25360./2187., 64448./6561., -212./729., 0., 0., 0.},
                                                                             {9017./3168., -355./33., 46732./5247., 49./176., -5103./ 18656., 0., 0.},
                                                                             {35./384., 0., 500./1113., 125./192., -2187./6784., 11./84., 0.}}};
    static constexpr vType cColumn = {0., 1./5., 3./10., 4./5., 8./9., 1., 1.};
    static constexpr vType bString1 = {35./384., 0., 500./1113., 125./192., -2187./6784., 11./84., 0.};
    static constexpr vType bString2 = {5179./57600., 0., 7571./16695., 393./640., -92097./339200., 187./2100., 1./40.};
    static constexpr unsigned int approximation = 5;
};
struct StepControl{
    double minStep;
    double maxStep;
    double tolerance;
    double initialStep;
};

template<typename Table, typename RHS>  // таблица бутчера и класс правой части f
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg& initialState,
        const typename RHS::Argument& endTime,
        const StepControl& stepControl,
        const RHS& rhs
);

class orbitAhrenstorf{
public:

    static constexpr unsigned int dim = 4;  // размерность задачи

    using Argument = double;  // тип аргумента, тип t

    using State = Eigen::Vector<double, dim>;  // состояние

    static constexpr Argument mu = 0.01227471;

    struct StateAndArg {
        State state;
        Argument arg;
    };

    /*** Вычисляет правую часть ДУ - функцию f***/
    Eigen::Vector<double, dim> calc(const StateAndArg &stateAndArg) const {
        double D1 = std::pow((stateAndArg.state(0) + mu)*(stateAndArg.state(0) + mu) + stateAndArg.state(2) * stateAndArg.state(2), 1.5);
        double D2 = std::pow((stateAndArg.state(0) - (1 - mu))*(stateAndArg.state(0) - (1 - mu)) + stateAndArg.state(2) * stateAndArg.state(2), 1.5);
        return Eigen::Vector<double, dim>{stateAndArg.state(1),
                                          stateAndArg.state(0) + 2. * stateAndArg.state(3) - (1 - mu)*(stateAndArg.state(0) + mu)/D1 - mu*(stateAndArg.state(0) - (1-mu))/D2,
                                          stateAndArg.state(3),
                                          stateAndArg.state(2) - 2. * stateAndArg.state(1) - (1 - mu)*stateAndArg.state(2)/D1 - mu * stateAndArg.state(2)/D2
                                          };
    }
};
/*
template<typename V1, typename V2>
V1 vpv(V1 vector1, const V2& vector2){
    for(std::size_t i = 0; vector1.size(); i++){
        vector1[i]+=vector2[i];
    }
    return vector1;
}

template<typename kType, typename fieldType>
kType k2v(fieldType f, kType k){
    for(auto& it:k){
        it*=f;
    }
    return k;
}

*/
template<typename Table, typename Arg>
Arg dot(const typename Table::vType &column, std::size_t row) {
    Arg result = Table::table[row][0] * column[0];;
    for (std::size_t i = 1; i < column.size(); i++) {
        result += Table::table[row][i] * column[i];
    }
    return result;
}

template<typename Table, typename Arg>
Arg v2v(const typename Table::vType &bString, const std::array<Arg, Table::stages> &column) {
    if (column.empty()) throw std::invalid_argument("bad arguments");
    Arg result = bString[0] * column[0];

    for (std::size_t i = 1; i < column.size(); i++) {
        result += bString[i] * column[i];
    }
    return result;
}

template<typename Table, typename RHS, typename fType, typename uType, typename rType>
std::pair<uType, uType> uzNextStep(const uType &uCurrent, const RHS &rhs, rType step) {
    std::array<fType, Table::stages> k{};
    k[0] = rhs.calc(uCurrent);
    k[1] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 1), uCurrent.arg + step * Table::cColumn[1]});
    k[2] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 2), uCurrent.arg + step * Table::cColumn[2]});
    k[3] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 3), uCurrent.arg + step * Table::cColumn[3]});
    k[4] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 4), uCurrent.arg + step * Table::cColumn[4]});
    k[5] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 5), uCurrent.arg + step * Table::cColumn[5]});
    k[6] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 6), uCurrent.arg + step * Table::cColumn[6]});
    k[7] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 7), uCurrent.arg + step * Table::cColumn[7]});
    //std::cout<<std::setprecision(10)<<k[0]<<" "<<k[1]<<" "<<k[2]<<" "<<k[3]<<"\n";
    return {{uCurrent.state + step * v2v<Table, fType>(Table::bString1, k), uCurrent.arg + step},
            {uCurrent.state + step * v2v<Table, fType>(Table::bString2, k), uCurrent.arg + step}};
}

template<typename rType, typename uType>
decltype(auto) hNextStep(const StepControl& stepControl, rType stepCurrent,const std::pair<uType, uType>& uz){
    auto r = std::sqrt((uz.first.state - uz.second.state).dot(uz.first.state - uz.second.state));
    //std::cout<<"r = "<<uz.second.state <<"\n";
    auto s = std::pow(stepControl.tolerance*stepCurrent/(2.*r),1./5);
    auto hOpt = s*stepCurrent;
    if(hOpt < stepControl.minStep) {
        //std::cout<<stepControl.minStep<<"\n";
        return stepControl.minStep;
    }
    if(hOpt > stepControl.maxStep) {
        //std::cout<<stepControl.maxStep<<"\n";
        return stepControl.maxStep;
    }
    //std::cout<< hOpt<<"\n";
    return hOpt;
}

template<typename Table, typename RHS>
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg& initialState,
        const typename RHS::Argument& endTime,
        const StepControl& stepControl,
        const RHS& rhs
){
    using utype = typename RHS::StateAndArg;
    using ftype = Eigen::Vector<double, RHS::dim>;
    using argType = typename RHS::Argument;
    std::vector<utype> uVector;
    uVector.reserve(int(endTime/stepControl.initialStep));
    uVector.push_back(initialState);
    argType timeCurrent = initialState.arg;
    std::pair<utype, utype>uzCurrent = {initialState, initialState};


    argType stepCurrent = stepControl.initialStep;


    while (timeCurrent + stepCurrent < endTime){
        uzCurrent = uzNextStep<Table, RHS, ftype, utype, double>(uzCurrent.first, rhs, stepCurrent); //then delete
        timeCurrent +=stepCurrent;
        stepCurrent = hNextStep<double, utype>(stepControl, stepCurrent, uzCurrent);
        uVector.push_back(uzCurrent.first);
    }
    if((endTime - timeCurrent) > stepControl.minStep){
        uzCurrent = uzNextStep<Table, RHS, ftype, utype, double>(uzCurrent.first, rhs, endTime - timeCurrent); //then delete
        uVector.push_back(uzCurrent.first);
    }
    return uVector;
}
