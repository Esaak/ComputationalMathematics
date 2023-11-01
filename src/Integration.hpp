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
template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable &func,  // Интегрируемая функция
        const typename ArgumentGetter<Callable>::Argument &start,  // начало отрезка
        const typename ArgumentGetter<Callable>::Argument &end,  // конец отрезка
        const typename ArgumentGetter<Callable>::Argument &acc // начало отчета результата
);

/* Функция производит интегрирование, разбивая отрезок на подотрезки длиной не более dx */
template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable &func,  // Интегрируемая функция
        const typename ArgumentGetter<Callable>::Argument &start,  // начало отрезка
        const typename ArgumentGetter<Callable>::Argument &end,  // конец отрезка
        const Dif<typename ArgumentGetter<Callable>::Argument> &dx,  // Длина подотрезка
        const typename ArgumentGetter<Callable>::Argument &acc // начало отчета результата
);

//structs with hardcode of Legendre nulls
template<std::size_t N>
struct nullLegendre;

/**find Legendre polynomial*/
//finds the values of Lejandre polynomials of n and n - 1 order at the point x
template<typename T, std::size_t N>
constexpr std::pair<T, T> legendrePolynomial(T x);


/**find derivative of Legendre polynomial*/
//you must pass the values of the n and n-1 order Lejandre polynomial at point x (stupid realization I agree)
template<typename T, std::size_t N>
constexpr T legendreDerivative(T x, const std::pair<T, T> &pair);

/**find a weights of Legendre polynomials of N order in [-1; 1]*/
template<typename T, std::size_t N>
constexpr T legendreWeight(T x);


//sqrt(15.)/5. = 0.7745966692414834
//sqrt(245 + 14sqrt(70))/21 = 0.906179845938664
//sqrt(245 - 14sqrt(70))/21 = 0.5384693101056831
template<std::size_t N>
struct nullLegendre;
template<>
struct nullLegendre<3> {
    constexpr static std::array<double, 3> nulls{-0.7745966692414834, 0., 0.7745966692414834};
};
template<>
struct nullLegendre<5> {
    constexpr static std::array<double, 5> nulls{-0.906179845938664, -0.5384693101056831, 0., 0.5384693101056831,
                                                 0.906179845938664};
};

//так себе
template<typename T, std::size_t N>
constexpr std::pair<T, T> legendrePolynomial(T x) {
    T p_prev = T(1);
    T p = x;
    T temp{};
    if (N == 0) return std::make_pair(p_prev, p_prev);
    if (N == 1) return std::make_pair(p_prev, p);
    for (std::size_t i = 1; i < N; i++) {
        temp = (T(2) * T(i) + T(1)) / T(i + 1) * x * p - T(i) / (T(i + 1)) * p_prev;
        p_prev = p;
        p = temp;
    }
    return std::make_pair(p_prev, p);
}

template<typename T, std::size_t N>
constexpr T legendreDerivative(T x, const std::pair<T, T> &pair) {
    return N / (1 - x * x) * (pair.first - x * pair.second);
}

template<typename T, std::size_t N>
constexpr T legendreWeight(T x) {
    std::pair<T, T> legendrePol = legendrePolynomial<T, N>(x);
    T polDerive = legendreDerivative<T, N>(x, legendrePol);
    return T(2) / ((T(1) - x * x) * (polDerive * polDerive));
}

template<typename T>
T setShift(T point, T start, T end) {
    return (start + end) / T(2) + (end - start) / T(2) * point;
}

template<typename Type, std::size_t N>
struct legendreData {
    std::array<Type, N> nulls;
    std::array<Type, N> weights;
};

template<typename Type>
struct default_id_trait{
    static Type id(){return Type(0.);}
};

template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable &func,
        const typename ArgumentGetter<Callable>::Argument &start,
        const typename ArgumentGetter<Callable>::Argument &end,
        const typename ArgumentGetter<Callable>::Argument &acc) {
    using arg = typename ArgumentGetter<Callable>::Argument;


    legendreData<arg, N> data;
    data.nulls = nullLegendre<N>::nulls;

    std::transform(data.nulls.begin(), data.nulls.end(), data.weights.begin(),
                   [](auto a) { return legendreWeight<decltype(a), N>(a); });

    arg result = acc;
    for (std::size_t it = 0; it != data.nulls.size(); it++) {
        result += func(setShift(data.nulls[it], start, end)) * data.weights[it];
    }

    return result * (end - start) / 2.;
}


template<typename Callable, std::size_t N>
decltype(auto) integrate(
        const Callable &func,
        const typename ArgumentGetter<Callable>::Argument &start,
        const typename ArgumentGetter<Callable>::Argument &end,
        const Dif<typename ArgumentGetter<Callable>::Argument> &dx,
        const typename ArgumentGetter<Callable>::Argument &acc
) {
    using arg = typename ArgumentGetter<Callable>::Argument;

    arg result = acc;
    const int secNum = static_cast<int>((end - start) / dx);

    for (std::size_t i = 0; i < secNum; i++) {
        result += integrate<Callable, N>(func, start + arg(i) * dx, start + arg(i + 1) * dx, acc);
    }

    result += integrate<Callable, N>(func, start + arg(secNum) * dx, end, acc);
    return result;
}



#endif //COMPMATH_INTEGRATION_HPP
