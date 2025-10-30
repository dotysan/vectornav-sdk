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

#ifndef VN_MATRIX_HPP_
#define VN_MATRIX_HPP_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <limits>

#include "vectornav/Debug.hpp"

namespace VN
{

template <uint16_t m, uint16_t n, typename T>
struct Matrix
{
    Matrix(T val = 0) noexcept { std::fill(_data.begin(), _data.end(), val); }

    Matrix(std::initializer_list<T> init) noexcept
    {
        VN_ASSERT(m * n == init.size());
        std::copy(init.begin(), init.end(), _data.begin());
    }

    Matrix(const std::array<T, m * n>& init) noexcept { _data = init; }

    static Matrix identity()
    {
        static_assert(m == n);
        Matrix<m, m, T> nm;
        for (uint16_t i = 0; i < m; i++) { nm(i, i) = 1; };
        return nm;
    }

    inline static Matrix null() { return Matrix<m, m, T>{}; }

    // Compound Assignment Operator Overloads /////////////////////////////////////////////////////
    const T& operator()(uint16_t row, uint16_t col) const
    {
        VN_ASSERT(row < m && col < n);
        return _data[col + row * n];
    }

    T& operator()(uint16_t row, uint16_t col)
    {
        VN_ASSERT(row < m && col < n);
        return _data[col + row * n];
    }

    const T& operator()(uint16_t row) const
    {
        VN_ASSERT(row < m * n);
        return _data[row];
    }

    T& operator()(uint16_t row)
    {
        VN_ASSERT(row < m * n);
        return _data[row];
    }

    T& operator[](uint16_t idx) { return _data[idx]; }

    const T& operator[](uint16_t idx) const { return _data[idx]; }

    constexpr uint16_t rows() const { return m; }

    constexpr uint16_t cols() const { return n; }

    constexpr T* data() noexcept { return _data.data(); }

    constexpr const T* data() const noexcept { return _data.data(); }

    constexpr uint16_t size() const noexcept { return _data.size(); }

    using iterator = typename std::array<T, m * n>::iterator;
    using const_iterator = typename std::array<T, m * n>::const_iterator;

    constexpr iterator begin() noexcept { return _data.begin(); }
    constexpr const_iterator begin() const noexcept { return _data.begin(); }
    constexpr iterator end() noexcept { return _data.end(); }
    constexpr const_iterator end() const noexcept { return _data.end(); }

    constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }
    constexpr const_iterator cend() const noexcept { return _data.cend(); }

private:
    std::array<T, m * n> _data = {0};
};

template <uint16_t lhs_m, uint16_t lhs_n, typename lhs_T>
Matrix<lhs_m, lhs_n, lhs_T>& operator-(Matrix<lhs_m, lhs_n, lhs_T>& mat)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] = -mat[i]; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator*=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const S rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] *= rhs; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator/=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const S rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] /= rhs; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator+=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const S rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] += rhs; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator-=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const S rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] -= rhs; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, uint16_t rhs_m, uint16_t rhs_n, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator+=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const Matrix<rhs_m, rhs_n, S>& rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] += rhs[i]; }
    return mat;
}

template <uint16_t lhs_m, uint16_t lhs_n, uint16_t rhs_n, uint16_t rhs_m, typename lhs_T, typename S>
Matrix<lhs_m, lhs_n, lhs_T>& operator-=(Matrix<lhs_m, lhs_n, lhs_T>& mat, const Matrix<rhs_m, rhs_n, S>& rhs)
{
    for (uint16_t i = 0; i < (lhs_m * lhs_n); i++) { mat[i] -= rhs[i]; }
    return mat;
}

template <uint16_t m, uint16_t n, uint16_t r, typename T, typename S>
Matrix<m, r, T> mat_mul(const Matrix<m, n, T>& lhs, const Matrix<n, r, S>& rhs)
{
    // columns from the matrix must match rows of the input matrix
    Matrix<m, r, T> mat;
    // Remember, this matrix is stored in column order
    for (uint16_t row = 0; row < m; row++)
    {
        for (uint16_t col = 0; col < r; col++)
        {
            uint16_t cell = row * r + col;
            for (uint16_t i = 0; i < n; i++) { mat[cell] += lhs[(row * n) + i] * rhs[(i * r + col)]; }
        }
    }

    return mat;
}

template <typename T, typename S>
Matrix<2, 2, T> mat_mul(const Matrix<2, 2, T>& lhs, const Matrix<2, 2, S>& rhs)
{
    Matrix<2, 2, T> mat;

    mat[0] = lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0);
    mat[1] = lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1);
    mat[2] = lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0);
    mat[3] = lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1);

    return mat;
}

template <typename T, typename S>
Matrix<2, 1, T> mat_mul(const Matrix<2, 2, T>& lhs, const Matrix<2, 1, S>& rhs)
{
    Matrix<2, 1, T> mat;

    mat[0] = lhs(0, 0) * rhs[0] + lhs(0, 1) * rhs[1];
    mat[1] = lhs(1, 0) * rhs[0] + lhs(1, 1) * rhs[1];

    return mat;
}

template <typename T, typename S>
Matrix<3, 3, T> mat_mul(const Matrix<3, 3, T>& lhs, const Matrix<3, 3, S>& rhs)
{
    Matrix<3, 3, T> mat;

    mat[0] = lhs[0] * rhs[0] + lhs[1] * rhs[3] + lhs[2] * rhs[6];
    mat[1] = lhs[0] * rhs[1] + lhs[1] * rhs[4] + lhs[2] * rhs[7];
    mat[2] = lhs[0] * rhs[2] + lhs[1] * rhs[5] + lhs[2] * rhs[8];

    mat[3] = lhs[3] * rhs[0] + lhs[4] * rhs[3] + lhs[5] * rhs[6];
    mat[4] = lhs[3] * rhs[1] + lhs[4] * rhs[4] + lhs[5] * rhs[7];
    mat[5] = lhs[3] * rhs[2] + lhs[4] * rhs[5] + lhs[5] * rhs[8];

    mat[6] = lhs[6] * rhs[0] + lhs[7] * rhs[3] + lhs[8] * rhs[6];
    mat[7] = lhs[6] * rhs[1] + lhs[7] * rhs[4] + lhs[8] * rhs[7];
    mat[8] = lhs[6] * rhs[2] + lhs[7] * rhs[5] + lhs[8] * rhs[8];

    return mat;
}

template <typename T, typename S>
Matrix<3, 1, T> mat_mul(const Matrix<3, 3, T>& lhs, const Matrix<3, 1, T>& rhs)
{
    Matrix<3, 1, T> mat;

    mat[0] = lhs(0, 0) * rhs[0] + lhs(0, 1) * rhs[1] + lhs(0, 2) * rhs[2];
    mat[1] = lhs(1, 0) * rhs[0] + lhs(1, 1) * rhs[1] + lhs(1, 2) * rhs[2];
    mat[2] = lhs(2, 0) * rhs[0] + lhs(2, 1) * rhs[1] + lhs(2, 2) * rhs[2];

    return mat;
}

// Arithmetic Operator Overloads /////////////////////////////////////////////////////////
template <uint16_t m, uint16_t n, uint16_t r, typename T, typename S>
Matrix<m, r, T> operator*(const Matrix<m, n, T>& lhs, const Matrix<n, r, S>& rhs)
{
    return mat_mul(lhs, rhs);
}

// Arithimetic Operations that can happen inplace
// Inplace Operator Overloads
template <uint16_t lhs_m, uint16_t lhs_n, typename T, typename S>
Matrix<lhs_m, lhs_n, T> operator*(Matrix<lhs_m, lhs_n, T> lhs, const S rhs)
{
    lhs *= rhs;
    return lhs;
}

template <uint16_t rhs_m, uint16_t rhs_n, typename T, typename S>
Matrix<rhs_m, rhs_n, T> operator*(const S lhs, Matrix<rhs_m, rhs_n, T> rhs)
{
    rhs *= lhs;
    return rhs;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename T, typename S>
Matrix<lhs_m, lhs_n, T> operator/(Matrix<lhs_m, lhs_n, T> lhs, const S rhs)
{
    lhs /= rhs;
    return lhs;
}

template <uint16_t lhs_m, uint16_t lhs_n, uint16_t rhs_m, uint16_t rhs_n, typename T, typename S>
Matrix<lhs_m, lhs_n, T> operator+(Matrix<lhs_m, lhs_n, T> lhs, const Matrix<rhs_m, rhs_n, S>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename T>
Matrix<lhs_m, lhs_n, T> operator+(Matrix<lhs_m, lhs_n, T> lhs, const T rhs)
{
    lhs += rhs;
    return lhs;
}

template <uint16_t rhs_m, uint16_t rhs_n, typename T>
Matrix<rhs_m, rhs_n, T> operator+(const T lhs, Matrix<rhs_m, rhs_n, T> rhs)
{
    rhs += lhs;
    return rhs;
}

template <uint16_t lhs_m, uint16_t lhs_n, uint16_t rhs_m, uint16_t rhs_n, typename T, typename S>
Matrix<lhs_m, lhs_n, T> operator-(Matrix<lhs_m, lhs_n, T> lhs, const Matrix<rhs_m, rhs_n, S>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <uint16_t lhs_m, uint16_t lhs_n, typename T>
Matrix<lhs_m, lhs_n, T> operator-(Matrix<lhs_m, lhs_n, T> lhs, const T rhs)
{
    lhs -= rhs;
    return lhs;
}

template <uint16_t rhs_m, uint16_t rhs_n, typename T>
Matrix<rhs_m, rhs_n, T> operator-(const T lhs, Matrix<rhs_m, rhs_n, T> rhs)
{
    rhs -= lhs;
    return rhs;
}

template <uint16_t m, uint16_t n, typename T>
bool operator==(const Matrix<m, n, T>& lhs, const Matrix<m, n, T>& rhs)
{
    static_assert(std::numeric_limits<T>::is_integer);
    return std::equal(&lhs[0], &lhs[m * n], &rhs[0]);
}

// // Common functions for working with matrices.
template <uint16_t m, uint16_t n, typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<m, n, T>& mat)
{
    std::string str = "[";

    for (uint16_t i = 0; i < m; i++)
    {
        str += '(';
        for (uint16_t j = 0; j < n; j++) { str += (std::to_string(mat(i, j)) + ", "); }
        str.pop_back();
        str.back() = ')';
    }
    str += "]";

    out << str;
    return out;
}

template <uint16_t m, uint16_t n, typename T>
Matrix<m, n, T> element_sqrt(Matrix<m, n, T> mat)
{
    for (uint16_t i = 0; i < m * n; i++) { mat[i] = std::sqrt(mat[i]); }
    return mat;
}

template <uint16_t m, uint16_t n, typename T>
Matrix<m, n, T> element_add(Matrix<m, n, T> mat, const Matrix<m, n, T>& rhs)
{
    for (uint16_t i = 0; i < m * n; i++) { mat[i] += rhs[i]; }
    return mat;
}

template <uint16_t m, uint16_t n, typename T>
Matrix<m, n, T> element_mul(Matrix<m, n, T> mat, const Matrix<m, n, T>& rhs)
{
    for (uint16_t i = 0; i < m * n; i++) { mat[i] *= rhs[i]; }
    return mat;
}

template <uint16_t m, uint16_t n, typename T>
Matrix<m, n, T> element_div(Matrix<m, n, T> mat, const Matrix<m, n, T>& rhs)
{
    for (uint16_t i = 0; i < m * n; i++) { mat[i] /= rhs[i]; }
    return mat;
}

using Mat2i = Matrix<2, 2, int>;

using Mat3i = Matrix<3, 3, int>;

using Mat2f = Matrix<2, 2, float>;

using Mat3f = Matrix<3, 3, float>;

using Mat4f = Matrix<4, 4, float>;

using Mat2d = Matrix<2, 2, double>;

using Mat3d = Matrix<3, 3, double>;

using Mat4d = Matrix<4, 4, double>;

using Vec2f = Matrix<2, 1, float>;

using Vec3f = Matrix<3, 1, float>;

using Vec4f = Matrix<4, 1, float>;

using Vec2d = Matrix<2, 1, double>;

using Vec3d = Matrix<3, 1, double>;
}  // namespace VN

#endif  // VN_MATRIX_HPP_
