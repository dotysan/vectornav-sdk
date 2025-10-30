// The MIT License (MIT)
// 
// VectorNav SDK (v0.22.0)
// Copyright (c) 2024 VectorNav Technologies, LLC
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef VN_LINEARALGEBRA_HPP_
#define VN_LINEARALGEBRA_HPP_

#include <cmath>
#include <numeric>

#include "vectornav/Debug.hpp"
#include "vectornav/TemplateLibrary/Matrix.hpp"

namespace VN
{
namespace Math
{

// Vector math
template <typename T, typename S>
T dot(const Matrix<3, 1, T>& lhs, const Matrix<3, 1, S>& rhs) noexcept
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

template <typename T, typename S>
T dot(const Matrix<4, 1, T>& lhs, const Matrix<4, 1, S>& rhs) noexcept
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
}

template <uint16_t m, typename T, typename S>
T dot(const Matrix<m, 1, T>& lhs, const Matrix<m, 1, S>& rhs) noexcept
{
    T sum = 0;
    for (uint16_t i = 0; i < m; i++) { sum += lhs[i] * rhs[i]; }
    return sum;
}

template <typename T>
Matrix<3, 1, T> cross(const Matrix<3, 1, T>& lhs, const Matrix<3, 1, T>& rhs) noexcept
{
    Matrix<3, 1, T> retMatrix;
    retMatrix[0] = lhs(1) * rhs(2) - lhs(2) * rhs(1);
    retMatrix[1] = lhs(2) * rhs(0) - lhs(0) * rhs(2);
    retMatrix[2] = lhs(0) * rhs(1) - lhs(1) * rhs(0);
    return retMatrix;
}

// If non-invertable it will return an identity matrix
template <uint16_t n, typename T>
Matrix<n, n, T> inverse(const Matrix<n, n, T>& mat) noexcept
{
    Matrix<n, n, T> ac = mat;
    Matrix<n, n, T> retMatrix;

    uint16_t i, j, iPass, imx, icol, irow;
    T det = 1;
    T temp, pivot, factor;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) { retMatrix(i, j) = 0; }
        retMatrix(i, i) = 1;
    }

    for (iPass = 0; iPass < n; iPass++)
    {
        imx = iPass;
        for (irow = iPass; irow < n; irow++)
        {
            if (std::abs(ac(irow, iPass)) > std::abs(ac(imx, iPass))) { imx = irow; }
        }

        if (imx != iPass)
        {
            for (icol = 0; icol < n; icol++)
            {
                temp = retMatrix(iPass, icol);
                retMatrix(iPass, icol) = retMatrix(imx, icol);
                retMatrix(imx, icol) = temp;
                if (icol >= iPass)
                {
                    temp = ac(iPass, icol);
                    ac(iPass, icol) = ac(imx, icol);
                    ac(imx, icol) = temp;
                }
            }
        }

        pivot = ac(iPass, iPass);
        det = det * pivot;

        if (std::abs(det) < std::numeric_limits<T>::epsilon())
        {
            return Matrix<n, n, T>::null();  // Matrix is not invertible
        }

        for (icol = 0; icol < n; icol++)
        {
            retMatrix(iPass, icol) = retMatrix(iPass, icol) / pivot;
            if (icol >= iPass) { ac(iPass, icol) = ac(iPass, icol) / pivot; }
        }

        for (irow = 0; irow < n; irow++)
        {
            if (irow != iPass)
            {
                factor = ac(irow, iPass);
                for (icol = 0; icol < n; icol++)
                {
                    if (irow != iPass)
                    {
                        retMatrix(irow, icol) -= factor * retMatrix(iPass, icol);
                        ac(irow, icol) -= factor * ac(iPass, icol);
                    }
                }
            }
        }
    }

    return retMatrix;  // Matrix inversion successful
}

template <typename T>
Matrix<2, 2, T> inverse(const Matrix<2, 2, T>& mat) noexcept
{
    Matrix<2, 2, T> nm({mat[3], -mat[1], -mat[2], mat[0]});

    T det = mat[0] * mat[3] - mat[1] * mat[2];

    if (std::abs(det) < 10 * std::numeric_limits<T>::epsilon()) { return Matrix<2, 2, T>::null(); }

    T invDet = 1 / det;
    return nm * invDet;
}

template <uint16_t n, typename T>
Matrix<n, 1, T> solveLinearSystemLU(Matrix<n, n, T> U, const Matrix<n, 1, T>& b) noexcept
{
    T det = 1.0;
    auto L = Matrix<n, n, T>();
    auto ri = std::array<int, n>();
    std::iota(ri.begin(), ri.end(), 0);
    Matrix<n, 1, T> x;

    // i indicates which column (from ri) we are reducing
    // LU Decomposition
    for (uint16_t i = 0; i < n - 1; i++)
    {
        // find row to pivot
        T pivot = 0;
        int row = 0;

        for (uint16_t j = i; j < n; j++)
        {
            T tmp = U(ri[j], i);
            if (std::fabs(pivot) < std::fabs(tmp))
            {
                row = j;
                pivot = tmp;
            }
        }

        det *= pivot;
        if (std::fabs(det) < 10 * std::numeric_limits<T>::epsilon()) { return x; }

        // keep track of pivot rows
        if (ri[i] != ri[row])
        {
            det = -det;
            std::swap(ri[i], ri[row]);
        }

        // Reduce columns to zero
        for (uint16_t j = i + 1; j < n; j++)
        {
            T c = -U(ri[j], i) / pivot;
            L(ri[j], i) = -c;
            for (uint16_t k = i; k < n; k++) { U(ri[j], k) += (c * U(ri[i], k)); }
        }
    }

    det *= U(ri[n - 1], n - 1);
    if (std::fabs(det) < 10 * std::numeric_limits<T>::epsilon()) { return x; }

    // solve Ly = Pb via forward sub
    for (int i = 0; i < static_cast<int>(n); i++)
    {
        x[i] = b[ri[i]];
        for (int j = 0; j < i; j++) { x[i] -= x[j] * L(ri[i], j); }
    }

    // solve Ux = y via backward sub
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--) { x[i] -= x[j] * U(ri[i], j); }
        x[i] /= U(ri[i], i);
    }

    return x;
}

template <uint16_t m, uint16_t n, typename T>
Matrix<n, m, T> transpose(const Matrix<m, n, T>& mat) noexcept
{
    Matrix<n, m, T> nm;

    for (uint16_t row = 0; row < m; row++)
    {
        for (uint16_t col = 0; col < n; col++) { nm(col, row) = mat(row, col); }
    }

    return nm;
}

template <typename T>
Matrix<3, 3, T> inverse(const Matrix<3, 3, T>& mat) noexcept
{
    Matrix<3, 3, T> nm;
    T det = mat(0, 0) * (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2)) - mat(0, 1) * (mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0)) +
            mat(0, 2) * (mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));

    if (std::abs(det) < std::numeric_limits<T>::epsilon()) { return Matrix<3, 3, T>::null(); }

    T invDet = 1 / det;

    nm(0, 0) = (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2)) * invDet;
    nm(0, 1) = (mat(0, 2) * mat(2, 1) - mat(0, 1) * mat(2, 2)) * invDet;
    nm(0, 2) = (mat(0, 1) * mat(1, 2) - mat(0, 2) * mat(1, 1)) * invDet;
    nm(1, 0) = (mat(1, 2) * mat(2, 0) - mat(1, 0) * mat(2, 2)) * invDet;
    nm(1, 1) = (mat(0, 0) * mat(2, 2) - mat(0, 2) * mat(2, 0)) * invDet;
    nm(1, 2) = (mat(1, 0) * mat(0, 2) - mat(0, 0) * mat(1, 2)) * invDet;
    nm(2, 0) = (mat(1, 0) * mat(2, 1) - mat(2, 0) * mat(1, 1)) * invDet;
    nm(2, 1) = (mat(2, 0) * mat(0, 1) - mat(0, 0) * mat(2, 1)) * invDet;
    nm(2, 2) = (mat(0, 0) * mat(1, 1) - mat(1, 0) * mat(0, 1)) * invDet;

    return nm;
}

template <typename T>
T sign(T val) noexcept
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
Matrix<3, 3, T> skew(const Matrix<3, 1, T>& vec) noexcept
{
    return {0, -vec[2], vec[1], vec[2], 0, -vec[0], -vec[1], vec[0], 0};
}

template <uint16_t m, uint16_t n, typename T>
T norm(const Matrix<m, n, T>& mat) noexcept
{
    T sum{0};
    for (uint16_t i = 0; i < m * n; i++) { sum += mat[i] * mat[i]; }

    return std::sqrt(sum);
}

template <uint16_t n, typename T>
uint16_t maxi(const Matrix<n, 1, T>& vec) noexcept
{
    uint16_t maxIndex = 0;
    for (uint16_t i = 1; i < n; i++) { maxIndex = (vec[i] > vec[maxIndex]) ? i : maxIndex; }
    return maxIndex;
}

template <uint16_t n, typename T>
uint16_t mini(const Matrix<n, 1, T>& vec) noexcept
{
    uint16_t maxIndex = 0;
    for (uint16_t i = 1; i < n; i++) { maxIndex = (vec[i] < vec[maxIndex]) ? i : maxIndex; }
    return maxIndex;
}

template <uint16_t m>
float condition(const Matrix<m, m, float>& A, const Matrix<m, m, float>& Ainv) noexcept
{
    return norm(A) * norm(Ainv);
}

template <uint16_t m, typename T>
std::optional<Matrix<m, 1, T>> normalize(Matrix<m, 1, T>& mat) noexcept
{
    T normM = norm(mat);
    if (normM < std::numeric_limits<T>::epsilon()) { return std::nullopt; }
    return std::make_optional<Matrix<m, 1, T>>(mat / normM);
}

template <uint16_t m, typename T>
Matrix<m, m, T> outer(const Matrix<m, 1, T>& lhs) noexcept
{
    Matrix<m, m, T> retMatrix;
    return lhs * transpose(lhs);
}

template <uint16_t m, typename T>
Matrix<m, m, T> outer(const Matrix<m, 1, T>& mat1, const Matrix<m, 1, T>& mat2) noexcept
{
    return mat1 * transpose(mat2);
}

template <uint16_t n1, uint16_t m, uint16_t n2, typename T>
Matrix<n1 + n2, m, T> vertcat(const Matrix<n1, m, T>& a, const Matrix<n2, m, T>& b) noexcept
{
    Matrix<n1 + n2, m, T> out;
    std::copy(a.begin(), a.end(), out.begin());
    std::copy(b.begin(), b.end(), out.begin() + n1 * m);
    return out;
}

template <uint16_t n, uint16_t m1, uint16_t m2, typename T>
Matrix<n, m1 + m2, T> horzcat(const Matrix<n, m1, T>& a, const Matrix<n, m2, T>& b) noexcept
{
    return transpose(vertcat(transpose(a), transpose(b)));
}

}  // namespace Math
}  // namespace VN

#endif  // VN_LINEARALGEBRA_HPP_
