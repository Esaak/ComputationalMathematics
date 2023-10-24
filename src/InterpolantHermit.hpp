
#pragma once

#include <array>
#include<cstdint>
/**
* xType - тип аргумента x.
* yType - тип значения функции y
* N - количество точек
*
* Рекомедую обратить внимание. Разность (xType - xType) не обязана быть типом xType
*/
template<typename xType, typename yType, unsigned int N >
class NewtonInterpolator {
    std::array<yType, 2 * N> splitDif;
    std::array<xType, N> points;
    std::array<xType, N> derivs;


    std::array<yType, 2 * N> first2stepSplitDif(const std::array<xType, N> &points, const std::array<yType, N>& values, const std::array<yType, N>& deriv);
public:
    NewtonInterpolator(const std::array<xType, N> &points, const std::array<yType, N>& values, const std::array<yType, N>& deriv) noexcept;
    yType interpolate(const xType& x) const noexcept;
    std::array<xType, N> getPointArrs() const{
        return points;
    }
    std::array<yType, 2 * N> getSplitDifArrs() const{
        return splitDif;
    }
};

template<typename xType, typename yType, unsigned int N>
std::array<yType, 2 * N> NewtonInterpolator<xType, yType, N>::first2stepSplitDif(const std::array<xType, N> &points,
                                                                                     const std::array<yType, N> &values,
                                                                                     const std::array<yType, N> &deriv) {
    std::array<yType, 2 * N> answ;
    answ[0] = values[0];
    answ[1] = deriv[0];
    for(std::size_t i = 2; i < 2 * N; i++){
        if(i % 2 == 0) {
            answ[i] = (values[i/2] - values[i/2 - 1]) / ((points[i/2] - points[i/2 - 1]));
        }
        else{
            answ[i] = deriv[i / 2];
        }
    }
    return answ;
}


template<typename xType, typename yType, unsigned int N >
NewtonInterpolator<xType, yType, N>::NewtonInterpolator(const std::array<xType, N> &points,
                                                        const std::array<yType, N> &values,
                                                        const std::array<yType, N> &deriv) noexcept: points(points), derivs(deriv){
    splitDif = first2stepSplitDif(points, values, deriv);

    yType temp1 = splitDif[1];
    for(uint32_t i = 1; i < 2 * N; i++){
        temp1 = splitDif[i];
        for(uint32_t j = 0; j + i + 1 < 2 * N; j++){
            yType temp = splitDif[j + i + 1];
            splitDif[j + i + 1] = (splitDif[j + i + 1] - temp1)/(points[(j + i + 1)/2] - points[j/2]);
            temp1 = temp;
        }
    }


}

template<typename xType, typename yType, unsigned int N>
yType NewtonInterpolator<xType, yType, N>::interpolate(const xType& x) const noexcept{
    constexpr std::int64_t n = 2 * N - 1;
    yType D = splitDif.back();
    for(std::int64_t i = 1; i < 2 * N;  i++){
        D = splitDif[n - i] + (x - points[(n - i)/2]) * D;
    }
    return D;
}
