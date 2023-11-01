#pragma once

#include <array>
#include <type_traits>
#include <cmath>


template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};


template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

namespace diny{
    decltype(auto) richardsonAnswer(const auto& result1N, const auto& result2N, double twoPowP){
        return result2N + (result2N - result1N)/(twoPowP - 1);
    }
}
template<typename Y, typename Callable, Y (*formula)(Y, Y, Callable&)>
struct fc{
    std::size_t p;
    Y operator()(Y start, Y end, Callable& func){
        return formula(start, end, func);
    }
};

template<typename Callable>
decltype(auto) integrateRunge(
        const Callable &func,
        auto cf,
        const typename ArgumentGetter<Callable>::Argument &start,
        const typename ArgumentGetter<Callable>::Argument &end,
        const Dif<typename ArgumentGetter<Callable>::Argument> &eps,
        const typename ArgumentGetter<Callable>::Argument &acc
) {
    using arg = typename ArgumentGetter<Callable>::Argument;
    using dif = Dif<typename ArgumentGetter<Callable>::Argument>;
    arg result2N = acc;
    arg result1N = acc;
    double twoPowP = std::pow(2, cf.p);
    int N = 2;
    dif sigma = 2 * eps*twoPowP;
    while(std::abs(sigma/(twoPowP - 1)) > eps && N < 1e15) {
        result2N = acc;
        result1N = acc;
        double dx2 = (-start + end) / (2 * N - 1);
        double dx1 = (-start + end) / (N - 1);
        for (std::size_t i = 0; i + 1 < N; i++) {
            result1N += cf(start + arg(i) * dx1, start + arg(i + 1) * dx1, func);
        }
        for (std::size_t i = 0; i + 1 < 2 * N; i++) {
            result2N += cf(start + arg(i) * dx2, start + arg(i + 1) * dx2, func);
        }
        sigma = result2N - result1N;
        N++;
    }
    return diny::richardsonAnswer(result1N, result2N, twoPowP);
}
