//
// Created by esaak on 9/14/23.
//

#ifndef COMPMATH_INTERPOLANT_HPP
#define COMPMATH_INTERPOLANT_HPP

#include <array>
#include<cstdint>

template<typename xType, typename yType, uint32_t N>
class NewtonInterpolator {
    std::array<yType, N> splitDif;
    std::array<xType, N> points;
public:
    NewtonInterpolator(const std::array<xType, N> &points, const std::array<yType, N>& values) noexcept: splitDif(values), points(points){
        yType temp1 = splitDif[0];
        for(uint32_t i = 0; i < N; i++){
            temp1 = splitDif[i];
            for(uint32_t j = 0; j + i + 1 < N; j++){
                yType temp = splitDif[j + i + 1];
                splitDif[j + i + 1] = (splitDif[j + i + 1] - temp1)/(points[j+ i + 1] - points[j]);
                temp1 = temp;
            }
        }
    }
    yType interpolate(const xType& x) const noexcept{
        int64_t n = N - 1;
        yType D = *splitDif.end();
        for(int64_t i = 1; i < N;  i++){
            D = splitDif[n - i] + (x - points[n - i]) * D;
        }
        return D;
    }
    std::array<xType, N> getPointArrs() const{
        return points;
    }
    std::array<yType, N> getSplitDifArrs() const{
        return splitDif;
    }
};


#endif //COMPMATH_INTERPOLANT_HPP
