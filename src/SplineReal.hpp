#pragma once

#include <vector>
#include <type_traits>

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

template<typename Type>
using DiffType = decltype(std::declval<Type>() - std::declval<Type>());

template<typename xType>
    using DeltaXType = DiffType<xType>;

template<typename xType, typename yType>
    using DerivType = DivisType<DiffType<yType>, DeltaXType<xType>>;

template<typename xType, typename yType>
    using Deriv2Type = DivisType<DiffType<DerivType<xType, yType>>, DeltaXType<xType>>;

template<typename xType, typename yType>
    using Deriv3Type = DivisType<DiffType<Deriv2Type<xType, yType>>, DeltaXType<xType>>;


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
    using DeltaXType = DiffType<xType>;
    using DerivType= DerivType<xType, yType>;
    using Deriv2Type= Deriv2Type<xType, yType>;
    using Deriv3Type= Deriv3Type<xType, yType>;

    struct spline{
        yType a;
        DerivType b;
        Deriv2Type c;
        Deriv3Type d;
        xType x;
    };
    std::array<spline, N + 1> splines;



public:
    CubicSpline( const std::array<xType, N + 1> &points,  // Значения x
                 const std::array<yType, N + 1>& values,  // значения y
                 const Deriv2Type& first,  // значение для левой второй производной
                 const Deriv2Type& second  // значение для правой второй производной
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
std::array<DerivType<cType, mType>, N> solve( const ThreeDiagonalMatrix<mType, N>& matrix,
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
CubicSpline<xType, yType, N>::CubicSpline(const std::array<xType, N + 1> &points,
                                          const std::array<yType, N + 1> &values,
                                          const Deriv2Type &first,
                                          const Deriv2Type &second) {
    constexpr xType diagEl = xType(2);
    xType h_2;
    std::array<yType, N> h;
    std::array<DerivType, N> u;

    std::array<Deriv2Type, N-1> column;
    ThreeDiagonalMatrix<DeltaXType, N-1>matrix;
    splines.back().a = values.back();
    splines.back().x = points.back();
    splines.back().c = second;
    splines[0] = {0,0,first,0,0};
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
        auto tmp = h[i]/h_2;
        matrix[i] = {tmp, diagEl, 1 - tmp};
    }
    h.back() = points.back() - points[column.size()];
    u.back() = (values.back() - values[column.size()])/h.back();
    column.back() = 6 * (u.back() - u[N - 2])/(points.back() - points[N - 2]);
    matrix.back() = {h[N - 2]/(points.back() - points[N-2]), diagEl, 0};
    auto answC = solve(matrix, column);
    for(std::size_t i = 0; i != answC.size(); i++){
        splines[i+1].c = answC[i];
        splines[i+1].b = (answC[i] + splines[i].c/2.) * h[i]/3. + u[i];
        splines[i+1].d = (answC[i] - splines[i].c) / h[i];
    }
    splines.back().b = (splines.back().c/3. + splines[answC.size()].c/6.) * h.back() + u.back();
    splines.back().d = (splines.back().c - splines[answC.size()].c) / h.back();

}

template<typename xType, typename yType, std::size_t N>
yType CubicSpline<xType, yType, N>::interpolate(const xType& x) const noexcept{
    auto answIt = std::lower_bound(splines.begin(), splines.end(), x, [](const spline &spline2, const xType& x){return x > spline2.x;});
    if(answIt == splines.end()) --answIt;
    auto it = std::distance(splines.begin(), answIt);
    std::tuple spline = {splines[it].a, splines[it].b, splines[it].c, splines[it].d, splines[it].x};
    yType result = std::get<0>(spline) - std::get<0>(spline);
    result = (result + std::get<3>(spline)) * (x - std::get<4>(spline))/3.;
    result = (result + std::get<2>(spline)) * (x - std::get<4>(spline))/2.;
    result = (result + std::get<1>(spline)) * (x - std::get<4>(spline));
    result +=std::get<0>(spline);
    return result;
}

///////////////////////////**************************//////////////////////////////
