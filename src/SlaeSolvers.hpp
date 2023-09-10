#ifndef COMPMATH_SLAESOLVERS_HPP
#define COMPMATH_SLAESOLVERS_HPP
#include "Matrix.hpp"

namespace solvers{
    namespace diny {
        template<typename RealType, std::uint32_t N>
        std::pair<Matrix<RealType>, std::vector<RealType>> partialPivot(Matrix<RealType> matrix, std::vector<RealType> b) {
            for (int i = 0; i < N; i++) {
                int pivot_row = i;
                for (int j = i + 1; j < N; j++) {
                    if (std::abs(matrix(j, i)) > std::abs(matrix(pivot_row,i))) {
                        pivot_row = j;
                    }
                }
                if (pivot_row != i) {
                    for (int j = i; j < N; j++) {
                        std::swap(matrix(i, j), matrix(pivot_row,j));
                    }
                    std::swap(b[i], b[pivot_row]);
                }
                for (int j = i + 1; j < N; j++) {
                    double factor = matrix(j,i) / matrix(i,i);
                    for (int k = i; k < N; k++) {
                        matrix(j,k) -= factor * matrix(i, k);
                    }
                    b[j]-=factor * b[i];
                }
            }
            return std::make_pair(matrix, b);
        }

        template<typename RealType, std::uint32_t N>
        std::array<RealType, N> backSubstitute(const Matrix<RealType> &matrix, const std::vector<RealType> &b) {
            std::array<RealType, N> answ;
            for (int i = static_cast<int>(N) - 1; i >= 0; i--) {
                double sum = 0;
                for (std::uint32_t j = i + 1; j < N; j++) {
                    if(j == N){
                        sum += b[i] *answ[j];
                    }
                    else {
                        sum += matrix(i, j) * answ[j];
                    }
                }
                answ[i] = (b[i] - sum) / matrix(i, i);
            }
            return answ;
        }

    }
    template<typename RealType, std::uint32_t N>
    std::array<RealType, N> Gauss(const Matrix<RealType> &matrix, const std::vector<RealType> &b){
        std::pair<Matrix<RealType>, std::vector<RealType>> temp_pair = diny::partialPivot<RealType, N>(matrix, b);
        return diny::backSubstitute<RealType, N>(temp_pair.first, temp_pair.second);
    }
}
#endif //COMPMATH_SLAESOLVERS_HPP
