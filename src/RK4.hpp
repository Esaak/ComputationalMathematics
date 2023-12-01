#pragma once

#include <array>
#include <Eigen/Eigen>

/* Это таблица Бутчера для метода Рунге-Кутты 4 порядка. Я ее не заполнил */
struct RK4Table {
    static constexpr unsigned int stages = 4;
    using vectorType = std::array<double, stages>;
    using rType = double;
    static constexpr std::array<vectorType, stages> table = {
            {{0., 0., 0., 0.}, {0.5, 0., 0., 0.}, {0., 0.5, 0., 0.}, {0., 0., 1., 0.}}};
    static constexpr vectorType cColumn = {0., 0.5, 0.5, 1};
    static constexpr vectorType bString = {1. / 6, 1. / 3, 1. / 3, 1. / 6};
};


template<typename v1Type,typename v2Type, std::size_t N>
v2Type v2v(const std::array<v1Type, N> &v1, const std::array<v2Type, N> &v2) {
    if (v2.empty() or v1.empty()) throw std::invalid_argument("bad arguments");
    v2Type result = v1[0] * v2[0];
    for (std::size_t i = 1; i < v2.size(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

template<typename Table, typename RHS, typename fType, typename uType>
uType uNextStep(const uType &uCurrent, const RHS &rhs, double step) {
    using rType = typename Table::rType;
    std::array<fType, Table::stages> k{};
    k[0] = rhs.calc(uCurrent);
    k[1] = rhs.calc({uCurrent.state + step * v2v<rType, fType, Table::stages>(Table::table[1], k), uCurrent.arg + step * Table::cColumn[1]});
    k[2] = rhs.calc({uCurrent.state + step * v2v<rType, fType, Table::stages>(Table::table[2], k), uCurrent.arg + step * Table::cColumn[2]});
    k[3] = rhs.calc({uCurrent.state + step * v2v<rType, fType, Table::stages>(Table::table[3], k), uCurrent.arg + step * Table::cColumn[3]});
    //std::cout<<std::setprecision(10)<<k[0]<<" "<<k[1]<<" "<<k[2]<<" "<<k[3]<<"\n";
    return {uCurrent.state + step * v2v<rType , fType, Table::stages>(Table::bString, k), uCurrent.arg + step};
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
        return Eigen::Vector<double, dim>{std::pow(stateAndArg.arg, 9)};
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
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg &initialState,
        const typename RHS::Argument &endTime,
        double step,
        const RHS &rhs
);

template<typename Table, typename RHS>
std::vector<typename RHS::StateAndArg> integrate(
        const typename RHS::StateAndArg &initialState,
        const typename RHS::Argument &endTime,
        double step,
        const RHS &rhs
) {
    using utype = typename RHS::StateAndArg;
    using ftype = Eigen::Vector<typename Table::rType, RHS::dim>;
    utype uCurrent = initialState;
    std::vector<utype> uVector{uCurrent};

    std::size_t numStep = endTime / step;
    uVector.reserve(numStep);



    for (std::size_t i = 1; i <= numStep; i++) {
        uCurrent = uNextStep<Table, RHS, ftype, utype>(uCurrent, rhs, step);
        uVector.push_back(uCurrent);
    }
    if(endTime - step * double(numStep) > 0) {
        uCurrent = uNextStep<Table, RHS, ftype, utype>(uCurrent, rhs,
                                                            endTime - step * double(numStep));
        uVector.push_back(uCurrent);
    }
    return uVector;
}