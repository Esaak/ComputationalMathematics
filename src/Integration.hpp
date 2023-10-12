#ifndef COMPMATH_INTEGRATION_HPP
#define COMPMATH_INTEGRATION_HPP


#include <array>
#include <type_traits>
#include <cmath>
#include <utility>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <ranges>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

/* Функция производит интегрирование на одном отрезке */
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
        const Callable &func,  // Интегрируемая функция
        const typename ArgumentGetter<Callable>::Argument &start,  // начало отрезка
        const typename ArgumentGetter<Callable>::Argument &end  // конец отрезка
);

/* Функция производит интегрирование, разбивая отрезок на подотрезки длиной не более dx */
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
        const Callable &func,  // Интегрируемая функция
        const typename ArgumentGetter<Callable>::Argument &start,  // начало отрезка
        const typename ArgumentGetter<Callable>::Argument &end,  // конец отрезка
        const Dif<typename ArgumentGetter<Callable>::Argument> &dx  // Длина подотрезка
);

//sqrt(15.)/5. = 0.7745966692414834
//sqrt(245 + 14sqrt(70))/21 = 0.906179845938664
//sqrt(245 - 14sqrt(70))/21 = 0.5384693101056831

struct nullLegendre{
    constexpr static std::array<double, 3> nullLejandre3{-0.7745966692414834, 0., 0.7745966692414834};
    constexpr static std::array<double, 5> nullLejandre5{-0.906179845938664, -0.5384693101056831, 0., 0.5384693101056831, 0.906179845938664};

};
//так себе
template<typename T, std::size_t N>
    constexpr std::pair<T,T> legendrePolynomial(T x){
        T p_prev = T(1);
        T p = x;
        T temp{};
        if(N == 0) return std::make_pair(p_prev, p_prev);
        if(N == 1) return std::make_pair(p_prev, p);
        for(std::size_t i = 1; i < N; i++){
            temp = (T(2)*T(i)+T(1))/T(i + 1)*x*p-T(i)/(T(i+1))*p_prev;
            p_prev = p;
            p = temp;
        }
        return std::make_pair(p_prev, p);
    }

template<typename T, std::size_t N>
    constexpr T legendreDerivative(T x, const std::pair<T, T>& pair){
        return N/(1-x*x)*(pair.first - x*pair.second);
    }

template<typename T, std::size_t N>
    constexpr T legendreWeight(T x){
        std::pair<T, T> legendrePol = legendrePolynomial<T, N>(x);
        T polDerive = legendreDerivative<T, N>(x, legendrePol);
        return T(2)/((T(1) - x*x)*(polDerive*polDerive));
    }


template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
        const Callable &func,
        const typename ArgumentGetter<Callable>::Argument &start,
        const typename ArgumentGetter<Callable>::Argument &end) {
    using arg = typename ArgumentGetter<Callable>::Argument;


    std::array<arg, N> weights;

    auto findNullLegendre = []()-> decltype(auto){
        if constexpr (nullLegendre::nullLejandre3.size() == N ){
            return nullLegendre::nullLejandre3;
        }
        if constexpr (nullLegendre::nullLejandre5.size() == N ){
            return nullLegendre::nullLejandre5;
        }
        throw std::invalid_argument("ой ой");
    };

    constexpr auto lNulls = findNullLegendre();
    //std::transform(weights.begin(), weights.end(), lNulls.begin(), [](auto a){return legendreWeight(a);});
    std::transform(lNulls.begin(), lNulls.end(), weights.begin(), [](auto a){return legendreWeight<decltype(a),N>(a);});
    decltype(weights) lNulls_z;
    std::transform(lNulls.cbegin(), lNulls.cend(), lNulls_z.begin(), [&start, &end](auto a){return (start + end)/2 + a*(- start + end)/2;});
    arg result= 0.;
    for(auto&& [z, weight]: std::views::zip(lNulls_z, weights)){
        result+=func(z) * weight;
    }
    return result *(end - start)/2.;
}


template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
        const Callable &func,
        const typename ArgumentGetter<Callable>::Argument &start,
        const typename ArgumentGetter<Callable>::Argument &end,
        const Dif<typename ArgumentGetter<Callable>::Argument> &dx
    ){
    using arg = typename ArgumentGetter<Callable>::Argument;

    arg result = 0;
    const int secNum =static_cast<int>((end - start)/dx);
    for(std::size_t i = 0; i < secNum; i++){
        result+= integrate<Callable, RealType, N>(func, start + arg(i)*dx, start + arg(i+1)*dx);
    }
    result+=integrate<Callable, RealType, N>(func, start + arg(secNum)*dx, end);
    return result;
}

#endif //COMPMATH_INTEGRATION_HPP
