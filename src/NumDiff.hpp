#ifndef COMPMATH_NUMDIFF_HPP
#define COMPMATH_NUMDIFF_HPP

#include "../src/SlaeSolvers.hpp"
template<typename RealType, std::uint64_t N>
struct DerivativeCoef {
    RealType centralCoef;
    std::array<RealType, N> otherCoefs;
};

constexpr std::uint64_t factorial(std::uint64_t n){
    std::uint64_t answ = 1;
    for(std::uint64_t i = 2; i <= n; i++){
        answ*=i;
    }
    return answ;
}

template<typename RealType, std::uint64_t N>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points) noexcept{
    Matrix<RealType, N + 1> matrix;
    std::array<RealType, N+1> b{};
    b[1] = RealType(1);
    std::for_each_n(matrix.begin()->begin(), N + 1, [](auto& n){ n = static_cast<RealType>(1);});
    for(std::uint64_t i = 0; i < N; i++){
        matrix[i+1][0] = 0;
        for(std::uint64_t j = 0; j < N; j++){
            matrix[i + 1][j + 1] = matrix[i][j + 1] * points[j];
            matrix[i + 1][j + 1] /= (i + 1);
        }
    }
    std::array<RealType, N + 1> gaussAnsw = solvers::Gauss<RealType, N + 1>(matrix, b);
    DerivativeCoef<RealType, N>answ;
    answ.centralCoef = gaussAnsw[0];
    std::copy(gaussAnsw.begin() + 1, gaussAnsw.end(), answ.otherCoefs.begin());
    return answ;
}

template<typename RealType, unsigned int N, unsigned int L>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points) noexcept{
    Matrix<RealType, N + 1> matrix;
    std::array<RealType, N+1> b{};
    b[L] = RealType(1);
    std::for_each_n(matrix.begin()->begin(), N + 1, [](auto& n){ n = static_cast<RealType>(1);});
    for(std::uint64_t i = 0; i < N; i++){
        matrix[i + 1][0] = 0;
        for(std::uint64_t j = 0; j < N; j++){
            matrix[i + 1][j + 1] = matrix[i][j + 1] * points[j];
            matrix[i + 1][j + 1] /= (i + 1);
        }
    }
    std::array<RealType, N + 1> gaussAnsw = solvers::Gauss<RealType, N + 1>(matrix, b);
    DerivativeCoef<RealType, N>answ;
    answ.centralCoef = gaussAnsw[0];
    std::copy(gaussAnsw.begin() + 1, gaussAnsw.end(), answ.otherCoefs.begin());
    return answ;
}

#endif //COMPMATH_NUMDIFF_HPP