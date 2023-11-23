#pragma once


#include <cstdio>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename Callable, typename RealType>
decltype(auto) solve(
        const Callable& func,                                             // функция F
        const RealType& tau,                                              // шаг тау
        const typename ArgumentGetter<Callable>::Argument& initialGuess,  // начальное приближение
        const unsigned int nIteration                                     // количество итераций
);

template<typename Callable, typename RealType>
decltype(auto) solve(
        const Callable& func,
        const RealType& tau,
        const typename ArgumentGetter<Callable>::Argument& initialGuess,
        const unsigned int nIteration
)
{
    using arg = typename ArgumentGetter<Callable>::Argument;
    arg answer_current = initialGuess;
    arg answer_next = initialGuess;
    for(auto i = 0; i < nIteration; i++){
        answer_next = answer_current + tau * func(answer_current);
    }
    return answer_next;
}
