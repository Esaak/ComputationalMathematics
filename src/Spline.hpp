#ifndef COMPMATH_SPLINE_HPP
#define COMPMATH_SPLINE_HPP

#include <vector>
#include <type_traits>
#include <stdexcept>

/** класс для работы с трехдиагональной матрицей **/
template<typename Type>
class ThreeDiagonalMatrix;

template<typename numeratorType, typename denominatorType>
using DivisType = decltype(std::declval<numeratorType>() / std::declval<denominatorType>());

/** Функция для решения методм  прогонки **/
template<typename mType, typename cType>
std::vector<DivisType<cType, mType>> solve( const ThreeDiagonalMatrix<mType>& matrix,
                                            const std::vector<cType>& column);



/**
* xType - тип аргумента x.
* yType - тип значения функции y
*/
template<typename xType, typename yType>
class CubicSpline {
    /*** Какие-то поля ***/

public:
    CubicSpline( const std::vector<xType> &points,  // Значения x
                 const std::vector<yType>& values  // значения y
    ){

    }

    yType interpolate(const xType& x) const noexcept;
};



template<typename Type>
    class ThreeDiagonalMatrix{
    private:
    struct Triads {
        Type a;
        Type b;
        Type c;
    };

    std::vector<Triads> data;
    std::size_t N;
    public:
    std::size_t size() const {
        return N;
    }

    void change_matrix(const std::vector<Type> &a, const std::vector<Type> &b, const std::vector<Type> &c) {
        data.reserve(a.size());
        N = a.size();
        for (std::size_t i = 0; i < a.size(); i++) {
            data[i].a = a[i];
            data[i].b = b[i];
            data[i].c = c[i];
        }
    }

    Triads &operator[](const std::size_t i) {
        return data[i];
    }

    const Triads &operator[](const std::size_t i) const {
        return data[i];
    }


    const Type &operator()(const std::size_t i, const std::size_t j) const {
        if (j + 1 == i) {
            return data[i].a;
        } else if (j == i) {
            return data[i].b;
        } else if (j == i + 1) {
            return data[i].c;
        }
        throw std::invalid_argument("invalid argument");
    }

    Type &operator()(std::size_t i, std::size_t j) {
        if (j + 1 == i) {
            return data[i].a;
        } else if (j == i) {
            return data[i].b;
        } else if (j == i + 1) {
            return data[i].c;
        }
        throw std::invalid_argument("invalid argument");
    }

};




template<typename mType, typename cType>
std::vector<DivisType<cType, mType>> solve( const ThreeDiagonalMatrix<mType>& matrix,
                                            const std::vector<cType>& column) {
    std::vector<cType> X = column;
    std::vector<cType> Temp(X.size());

    int N = static_cast<int>(X.size()) - 1;

    Temp[0] = matrix(0, 0 + 1) / matrix(0, 0);
    X[0] /= matrix(0, 0);
    for (int i = 1; i < N; i++) {
        Temp[i] = matrix(i, i + 1) / (matrix(i, i) - matrix(i, i - 1) * Temp[i - 1]);
        X[i] = (X[i] - matrix(i, i - 1) * X[i - 1]) / (matrix(i, i) - matrix(i, i - 1) * Temp[i - 1]);
    }
    X.back() = (X.back() - matrix(N, N - 1) * X[N - 1]) / (matrix(N, N) - matrix(N, N - 1) * Temp[N - 1]);

    for (int i = N; i-- > 0;) {
        X[i] -= Temp[i] * X[i + 1];
    }
    return X;

}

#endif //COMPMATH_SPLINE_HPP
