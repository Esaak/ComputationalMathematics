#pragma once

#include <array>
#include <Eigen/Eigen>

/* Это таблица Бутчера для метода Рунге-Кутты 4 порядка. Я ее не заполнил */
struct RK4Table {
    static constexpr unsigned int stages = 4;
    using vectorType = std::array<double, stages>;
    static constexpr std::array<vectorType, stages> table = {
            {{0., 0., 0., 0.}, {0.5, 0., 0., 0.}, {0., 0.5, 0., 0.}, {0., 0., 1., 0.}}};
    static constexpr vectorType cColumn = {0., 0.5, 0.5, 1};
    static constexpr vectorType bString = {1. / 6, 1. / 3, 1. / 3, 1. / 6};
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
Arg dot(const std::array<Arg, Table::stages> &column, std::size_t row) {
    Arg result = Table::table[row][0] * column[0];;
    for (std::size_t i = 1; i < column.size(); i++) {
        result += Table::table[row][i] * column[i];
    }
    return result;
}

template<typename Table, typename Arg>
Arg v2v(const std::array<Arg, Table::stages> &column) {
    if (column.empty()) throw std::invalid_argument("bad arguments");
    Arg result = Table::bString[0] * column[0];

    for (std::size_t i = 1; i < column.size(); i++) {
        result += Table::bString[i] * column[i];
    }
    return result;
}

template<typename Table, typename RHS, typename fType, typename uType, typename rType>
uType uNextStep(const uType &uCurrent, const RHS &rhs, rType step) {
    std::array<fType, Table::stages> k{};
    k[0] = rhs.calc(uCurrent);
    k[1] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 1), uCurrent.arg + step * Table::cColumn[1]});
    k[2] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 2), uCurrent.arg + step * Table::cColumn[2]});
    k[3] = rhs.calc({uCurrent.state + step * dot<Table, fType>(k, 3), uCurrent.arg + step * Table::cColumn[3]});
    //std::cout<<std::setprecision(10)<<k[0]<<" "<<k[1]<<" "<<k[2]<<" "<<k[3]<<"\n";
    return {uCurrent.state + step * v2v<Table, fType>(k), uCurrent.arg + step};
}

class firstTask {
public:

    static constexpr unsigned int dim = 1;  // размерность задачи

    using Argument = double;  // тип аргумента, тип t

    using State = Eigen::Vector<double, dim>;  // состояние

    struct StateAndArg {
        State state;
        Argument arg;
    };

    /*** Вычисляет правую часть ДУ - функцию f***/
    Eigen::Vector<double, dim> calc(const StateAndArg &stateAndArg) const {
        return Eigen::Vector<double, dim>{stateAndArg.arg * stateAndArg.arg * stateAndArg.arg};
    }
};

class secondTask {
public:

    static constexpr unsigned int dim = 2;  // размерность задачи

    using Argument = double;  // тип аргумента, тип t

    using State = Eigen::Vector<double, dim>;  // состояние

    struct StateAndArg {
        State state;
        Argument arg;
    };

    /*** Вычисляет правую часть ДУ - функцию f***/
    Eigen::Vector<double, dim> calc(const StateAndArg &stateAndArg) const {
        return Eigen::Vector<double, dim>{stateAndArg.state(1), -stateAndArg.state(0)};
    }
};

//Сигнатура для метода интегрирования:
template<typename Table, typename RHS>
// таблица бутчера и класс правой части f
typename RHS::StateAndArg integrate(
        const typename RHS::StateAndArg &initialState,
        const typename RHS::Argument &endTime,
        double step,
        const RHS &rhs
);

template<typename Table, typename RHS>
typename RHS::StateAndArg integrate(
        const typename RHS::StateAndArg &initialState,
        const typename RHS::Argument &endTime,
        double step,
        const RHS &rhs,
        auto &output = nullptr
) {
    using utype = typename RHS::StateAndArg;
    using ftype = Eigen::Vector<double, RHS::dim>;
    utype uCurrent = initialState;

    utype uNext = uCurrent; //then delete

    std::size_t numStep = endTime / step;

    auto maxR = 0.;//then delete

    for (std::size_t i = 1; i <= numStep; i++) {
        //uCurrent = uNextStep<Table, RHS, ftype, utype, double>(uCurrent, rhs, step, i);
        uNext = uNextStep<Table, RHS, ftype, utype, double>(uCurrent, rhs, step); //then delete
        maxR = std::max(std::abs(uCurrent.state(0) - uNext.state(0)), maxR); //then delete
        //std::cout << uNext.state(0) << "\n";
        uCurrent = uNext; //then delete
    }
    //uCurrent = uNextStep<Table, RHS, ftype, utype, double>(uCurrent, rhs, endTime - step * double(numStep));
    if(endTime - step * double(numStep) > 0) {
        uNext = uNextStep<Table, RHS, ftype, utype, double>(uCurrent, rhs,
                                                            endTime - step * double(numStep)); //then delete
        //std::cout << uNext.state(0) << "\n";
    }
    maxR = std::max(std::abs(uCurrent.state(0) - uNext.state(0)), maxR); //then delete
    output << maxR << '\n';
    //return uCurrent;
    return uNext; //then delete
}