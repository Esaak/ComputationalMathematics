#pragma once


#include <cstdio>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};
template<typename T>
std::vector<T> operator *(T a,const std::vector<T> v){
    std::vector<T> answ = v;
    for(auto& it:answ){
        it *= a;
    }
    return answ;
}

template<typename T>
std::vector<T> operator +(const std::vector<T> v1, const std::vector<T> v2){
    std::vector<T> answ = v1;
    for(std::size_t i = 0; i< v1.size(); i++){
        answ[i] +=v2[i];
    }
    return answ;
}


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
        answer_current = answer_next;
    }
    return answer_next;
}
