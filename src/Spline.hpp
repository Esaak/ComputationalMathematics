#ifndef COMPMATH_SPLINE_HPP
#define COMPMATH_SPLINE_HPP

#include <vector>
#include <type_traits>
#include <stdexcept>
#include <tuple>

/** класс для работы с трехдиагональной матрицей **/
template<typename Type, std::size_t N>
class ThreeDiagonalMatrix{
private:
    struct Triads {
        Type a;
        Type b;
        Type c;
    };

    std::array<Triads, N> data;
public:
    std::size_t size() const;
    //void change_matrix(const std::array<Type, N> &a, const std::array<Type, N> &b, const std::array<Type, N> &c);
    Triads &operator[](std::size_t i);
    const Triads &operator[](std::size_t i) const;
    const Type &operator()(std::size_t i, std::size_t j) const;
    Type &operator()(std::size_t i, std::size_t j);
    const Triads &back() const;
    Triads &back();
};


template<typename numeratorType, typename denominatorType>
using DivisType = decltype(std::declval<numeratorType>() / std::declval<denominatorType>());

//template<typename fType, typename sType>
//using MullType = decltype(std::declval<fType>() * std::declval<sType>());

/** Функция для решения методм  прогонки **/
template<typename mType, typename cType, std::size_t N>
std::vector<DivisType<cType, mType>> solve( const ThreeDiagonalMatrix<mType, N>& matrix,
                                            const std::vector<cType>& column);



/**
* xType - тип аргумента x.
* yType - тип значения функции y
*/
template<typename xType, typename yType, std::size_t N>
class CubicSpline {

    struct spline{
        yType a;
        yType b;
        yType c;
        yType d;
        xType x;
    };
    std::array<spline, N + 1> splines;
    /*
    std::array<yType, N> a;
    std::array<yType, N> b;
    std::array<yType, N> c;
    std::array<yType, N> d;
    std::array<xType, N> x;
    */
public:
    CubicSpline( const std::array<xType, N + 1> &points,  // Значения x
                 const std::array<yType, N + 1>& values  // значения y
    );

    yType interpolate(const xType& x) const noexcept;
};
//////////////////////////////ThreeDiagonalMatrix definition //////////////////////////////

template<typename Type, std::size_t N>
std::size_t ThreeDiagonalMatrix<Type, N>::size() const {
    return N;
}

template<typename Type, std::size_t N>
ThreeDiagonalMatrix<Type, N>::Triads &ThreeDiagonalMatrix<Type, N>::operator[](std::size_t i) {
    return data[i];
}

template<typename Type, std::size_t N>
const ThreeDiagonalMatrix<Type, N>::Triads &ThreeDiagonalMatrix<Type, N>::operator[](std::size_t i) const {
    return data[i];
}
/*
template<typename Type, std::size_t N>
void ThreeDiagonalMatrix<Type, N>::change_matrix(const std::array<Type, N> &a, const std::array<Type, N> &b, const std::array<Type, N> &c) {
    data.reserve(a.size());
    N = a.size();
    for (std::size_t i = 0; i < N; i++) {
        data[i].a = a[i];
        data[i].b = b[i];
        data[i].c = c[i];
    }
}
*/
template<typename Type, std::size_t N>
const Type &ThreeDiagonalMatrix<Type, N>::operator()(std::size_t i, std::size_t j) const {
    if (j + 1 == i) {
        return data[i].a;
    } else if (j == i) {
        return data[i].b;
    } else if (j == i + 1) {
        return data[i].c;
    }
}

template<typename Type, std::size_t N>
Type &ThreeDiagonalMatrix<Type, N>::operator()(std::size_t i, std::size_t j) {
    if (j + 1 == i) {
        return data[i].a;
    } else if (j == i) {
        return data[i].b;
    } else if (j == i + 1) {
        return data[i].c;
    }
}
template<typename Type, std::size_t N>
const ThreeDiagonalMatrix<Type, N>::Triads &ThreeDiagonalMatrix<Type, N>::back() const {
    return data.back();
}
template<typename Type, std::size_t N>
ThreeDiagonalMatrix<Type, N>::Triads &ThreeDiagonalMatrix<Type, N>::back(){
    return data.back();
}

///////////////////////////**************************//////////////////////////////


template<typename mType, typename cType, std::size_t N>
std::array<DivisType<cType, mType>, N> solve( const ThreeDiagonalMatrix<mType, N>& matrix,
                                            const std::array<cType, N>& column) {
    auto X = column;
    decltype(X) Temp;

    int N_1 = static_cast<int>(N) - 1;

    Temp[0] = matrix(0, 0 + 1) / matrix(0, 0);
    X[0] /= matrix(0, 0);
    for (int i = 1; i < N_1; i++) {
        Temp[i] = matrix(i, i + 1) / (matrix(i, i) - matrix(i, i - 1) * Temp[i - 1]);
        X[i] = (X[i] - matrix(i, i - 1) * X[i - 1]) / (matrix(i, i) - matrix(i, i - 1) * Temp[i - 1]);
    }
    X.back() = (X.back() - matrix(N_1, N_1 - 1) * X[N_1 - 1]) / (matrix(N_1, N_1) - matrix(N_1, N_1 - 1) * Temp[N_1 - 1]);

    for (int i = N_1; i-- > 0;) {
        X[i] -= Temp[i] * X[i + 1];
    }
    return X;

}

//////////////////////////////CubicSpline definition //////////////////////////////
template<typename xType, typename yType, std::size_t N>
CubicSpline<xType, yType, N>::CubicSpline(const std::array<xType, N + 1> &points, const std::array<yType, N + 1> &values){
    constexpr xType diagEl = xType(2);
    xType h_2;
    std::array<yType, N> h;
    std::array<xType, N> u;

    std::array<xType, N-1> column;
    ThreeDiagonalMatrix<xType, N-1>matrix;
    splines.back().a = values.back();
    splines.back().x = points.back();
    splines.back().c = 0;
    splines[0] = {0,0,0,0,0};
    h[0] = points[1] - points[0];
    h[1] = points[2] - points[1];
    h_2 = h[1] + h[0];
    u[1] = (values[2] - values[1])/h[1];
    u[0] = (values[1] - values[0])/h[0];

    matrix[0] = {0, diagEl, h[1]/h_2};

    column[0] = 6 * (u[1] - u[0])/h_2;

    for(std::size_t i = 0; i < N; i++){
        splines[i].a = values[i];
        splines[i].x = points[i];


        if( i < 1 || i + 2 > N) continue;
        h[i + 1] = points[i+2] - points[i+1];
        h_2 = h[i+1] + h[i];
        u[i + 1] = (values[i+2] - values[i + 1])/h[i+1];
        column[i] = 6 * (u[i + 1] - u[i])/h_2;
        matrix[i] = {h[i]/h_2, diagEl, h[i+1]/h_2};
    }
    h.back() = points.back() - *(points.end() -2);
    u.back() = (values.back() - *(values.end() - 2))/h.back();
    column.back() = 6 * (u.back() - *(u.end()-2))/(points.back() - *(points.end() - 3));
    matrix.back() = {h[N - 2]/(points[N] - points[N-2]), diagEl, 0};
    auto answC = solve(matrix, column);
    for(std::size_t i = 0; i != answC.size(); i++){
        splines[i+1].c = answC[i];
        splines[i+1].b = (answC[i] + splines[i].c/yType(2)) * h[i + 1]/yType(3) + u[i];
        splines[i+1].d = (answC[i] - splines[i].c) / h[i + 1];
    }
    splines.back().b = splines[answC.size()].c/yType(6) * h.back() + u[answC.size()];
    splines.back().d = -(splines[answC.size()].c) / h.back();

}

template<typename xType, typename yType, std::size_t N>
yType CubicSpline<xType, yType, N>::interpolate(const xType& x) const noexcept{
    auto answIt = std::lower_bound(splines.begin(), splines.end(), x, [](auto &spline, const xType &x){return spline.x < x;});
    if(answIt == splines.end()) --answIt;
    auto it = std::distance(splines.begin(), answIt);
    std::tuple spline = {splines[it].a, splines[it].b, splines[it].c, splines[it].d, splines[it].x};
    yType result = std::get<0>(spline) - std::get<0>(spline);
    result = (result + std::get<3>(spline)) * (x - std::get<4>(spline))/yType(3.);
    result = (result + std::get<2>(spline)) * (x - std::get<4>(spline))/yType(2.);
    result = (result + std::get<1>(spline)) * (x - std::get<4>(spline));
    result +=std::get<0>(spline);
    return result;
}

///////////////////////////**************************//////////////////////////////

#endif //COMPMATH_SPLINE_HPP
