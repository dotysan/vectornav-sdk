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

#ifndef VN_EIGENDECOMPOSITION_HPP_
#define VN_EIGENDECOMPOSITION_HPP_

#include <cmath>
#include <complex>

#include "vectornav/Debug.hpp"
#include "vectornav/TemplateLibrary/Matrix.hpp"

namespace VN
{
namespace Math
{

class EigenDecomposition
{
    static constexpr double _MACH_EPS = std::numeric_limits<double>::epsilon();

public:
    EigenDecomposition() : _maxIter{50} {}
    EigenDecomposition(int maxIter) : _maxIter{maxIter} {}

    template <uint16_t m, typename T>
    bool computeDecomposition(Matrix<m, m, T>& mat, Matrix<m, 1, T>& eigenValuesR, Matrix<m, 1, T>& eigenValuesI, Matrix<m, m, T>& eigenVectors) noexcept
    {
        if (m < 1) return true;  // Returned an error

        // Case where m = 1
        if (m == 1)
        {
            eigenVectors(0, 0) = static_cast<T>(1.0);
            eigenValuesR = Matrix<m, 1, T>{mat(0, 0)};
            eigenValuesI = Matrix<m, 1, T>{0.0};
            return false;
        }

        // Case where m > 1
        Matrix<m, 1, int> count(0);  // Initialize iteration counter
        Matrix<m, 1, T> scale(0.0);
        uint16_t low{0}, high{0};
        if (balanceMatrix(mat, scale, low, high)) return true;

        if (computeUpperHessenberg(mat, count, low, high)) return true;

        if (transformToUpperHessenberg(mat, count, low, high, eigenVectors)) return true;

        if (computeEigenValuesAndVectors(mat, count, eigenValuesR, eigenValuesI, eigenVectors, low, high)) return true;

        if (undoBalance(eigenVectors, scale, low, high)) return true;

        if (normalizeEigenVectors(eigenVectors, eigenValuesI)) return true;

        // while loop in n_eigeng
        uint16_t j{0};
        while (j < m)
        {
            T temp = static_cast<T>(0.0);
            if (eigenValuesI(j) < _MACH_EPS)
            {
                for (uint16_t i{0}; i < m; ++i) temp += eigenVectors(i, j) * eigenVectors(i, j);
                temp = std::sqrt(temp);
                for (uint16_t i{0}; i < m; ++i) eigenVectors(i, j) /= temp;
            }
            else
            {
                for (uint16_t i{0}; i < m; ++i) temp += eigenVectors(i, j) * eigenVectors(i, j);
                for (uint16_t i{0}; i < m; ++i) temp += eigenVectors(i, j + 1) * eigenVectors(i, j + 1);
                temp = std::sqrt(temp);
                for (uint16_t i{0}; i < m; ++i) eigenVectors(i, j) /= temp;
                for (uint16_t i{0}; i < m; ++i) eigenVectors(i, j + 1) /= temp;
                ++j;
            }
            ++j;
        }

        return false;
    }

protected:
    template <uint16_t m, typename T>
    bool balanceMatrix(Matrix<m, m, T>& mat, Matrix<m, 1, T>& scale, uint16_t& low, uint16_t& high) noexcept
    {
        int basis = computeBasis();
        T basisSquared = static_cast<T>(basis * basis);
        uint16_t n{0};
        uint16_t k{m - 1};
        uint16_t k0{m - 1};

        bool iter;
        do {
            uint16_t j;
            iter = false;
            for (uint16_t j_{0}; j_ <= k0; ++j_)
            {
                j = k0 - j_;
                T r{0};
                for (uint16_t i{0}; i <= k; ++i)
                    if (i != j) r += std::abs(mat(j, i));

                if (r == static_cast<T>(0.0))
                {
                    scale[k] = static_cast<T>(j);
                    if (j != k)
                    {
                        for (uint16_t i{0}; i <= k; ++i) std::swap(mat(i, j), mat(i, k));
                        for (uint16_t i{n}; i < m; ++i) std::swap(mat(j, i), mat(k, i));
                    }
                    --k;
                    iter = true;
                }
            }
        } while (iter);

        do {
            iter = false;
            for (uint16_t j{n}; j <= k; ++j)
            {
                T c{0};
                for (uint16_t i{n}; i <= k; ++i)
                    if (i != j) c += std::abs(mat(i, j));
                if (c == 0)
                {
                    scale[n] = static_cast<T>(j);
                    if (j != m)
                    {
                        for (uint16_t i{0}; i <= k; ++i) std::swap(mat(i, j), mat(i, n));
                        for (uint16_t i{n}; i < m; ++i) std::swap(mat(j, i), mat(n, i));
                    }
                    ++n;
                    iter = true;
                }
            }
        } while (iter);

        low = n;
        high = k;
        for (uint16_t i{n}; i != m; ++i) scale[i] = static_cast<T>(1.0);

        T g, f, s;
        do {
            iter = false;
            for (uint16_t i{n}; i <= k; ++i)
            {
                T c{0.0}, r{0.0};
                for (uint16_t j{n}; j <= k; ++j)
                {
                    if (j != i)
                    {
                        c += std::abs(mat(j, i));
                        r += std::abs(mat(i, j));
                    }
                }
                g = r / basis;
                f = static_cast<T>(1.0);
                s = c + r;

                while (c < g)
                {
                    f *= basis;
                    c *= basisSquared;
                }

                g = r * basis;
                while (c >= g)
                {
                    f /= basis;
                    c /= basisSquared;
                }

                if ((c + r) / f < static_cast<T>(0.95) * s)
                {
                    g = static_cast<T>(1.0) / f;
                    scale[i] *= f;
                    iter = true;
                    for (uint16_t j{n}; j < m; ++j) mat(i, j) *= g;
                    for (uint16_t j{0}; j <= k; ++j) mat(j, i) *= f;
                }
            }
        } while (iter);

        return false;
    }

    template <uint16_t m, typename T>
    bool undoBalance(Matrix<m, m, T>& mat, Matrix<m, 1, T>& scale, uint16_t low, uint16_t high) noexcept
    {
        for (uint16_t i{low}; i <= high; ++i)
        {
            const float s = scale(i);
            for (uint16_t j{0}; j < m; ++j) mat(i, j) *= s;
        }

        for (uint16_t i_{0}; i_ != low; ++i_)
        {
            const uint16_t i = low - i_ - 1;
            const uint16_t k = static_cast<uint16_t>(scale(i));
            if (k != i)
                for (uint16_t j{0}; j < m; ++j) std::swap(mat(i, j), mat(k, j));
        }

        for (uint16_t i{static_cast<uint16_t>(high + 1)}; i < m; ++i)
        {
            const uint16_t k = static_cast<uint16_t>(scale(i));
            for (uint16_t j{0}; j < m; ++j) std::swap(mat(i, j), mat(k, j));
        }

        return false;
    }

    template <uint16_t m, typename T>
    bool computeUpperHessenberg(Matrix<m, m, T>& mat, Matrix<m, 1, int>& count, uint16_t low, uint16_t high) noexcept
    {
        if (low > m || high > m) return true;  // Zero matrix

        uint16_t i, j, n;
        float x, y;
        for (n = low + 1; n < high; ++n)
        {
            i = n;
            x = 0.0;
            for (j = n; j <= high; ++j)
            {
                if (std::abs(mat(j, n - 1)) > std::abs(x))
                {
                    x = mat(j, n - 1);
                    i = j;
                }
            }

            count[n] = i;
            if (i != n)
            {
                for (j = n - 1; j < m; ++j) std::swap(mat(i, j), mat(n, j));
                for (j = 0; j <= high; ++j) std::swap(mat(j, i), mat(j, n));
            }

            if (x != 0.0)
            {
                for (i = n + 1; i <= high; ++i)
                {
                    y = mat(i, n - 1);
                    if (y != 0.0)
                    {
                        y = mat(i, n - 1) = y / x;
                        for (j = n; j < m; ++j) mat(i, j) -= y * mat(n, j);
                        for (j = 0; j <= high; ++j) mat(j, n) += y * mat(j, i);
                    }
                }  // end i
            }
        }  // end m

        return false;
    }

    template <uint16_t m, typename T>
    bool transformToUpperHessenberg(const Matrix<m, m, T>& mat, const Matrix<m, 1, int>& count, uint16_t low, uint16_t high, Matrix<m, m, T>& hes) noexcept
    {
        hes = Matrix<m, m, T>::identity();

        uint16_t j;
        for (uint16_t i_{static_cast<uint16_t>(low + 1)}; i_ != high; ++i_)
        {
            uint16_t i = high - i_;
            j = count(i);
            for (uint16_t k{static_cast<uint16_t>(i + 1)}; k <= high; ++k) hes(k, i) = mat(k, i - 1);

            if (i != j)
            {
                for (uint16_t k{i}; k <= high; ++k)
                {
                    hes(i, k) = hes(j, k);
                    hes(j, k) = static_cast<T>(0.0);
                }
                hes(j, i) = static_cast<T>(1.0);
            }
        }

        return false;
    }

    template <uint16_t m, typename T>
    bool computeEigenValuesAndVectors(Matrix<m, m, T>& hes, Matrix<m, 1, int>& count, Matrix<m, 1, T>& eigenValuesR, Matrix<m, 1, T>& eigenValuesI,
                                      Matrix<m, m, T>& eigenVectors, uint16_t low, uint16_t high) noexcept
    {
        // Compute eigenvalues and vectors using Francis QR algorithm
        for (uint16_t i{0}; i != m; ++i)
        {
            if (i < low || i > high)
            {
                eigenValuesR(i) = hes(i, i);
                eigenValuesI(i) = static_cast<T>(0.0);
                count(i) = 0;
            }
        }

        int iter;
        uint16_t en{high}, na, l, j, n{0};
        T t{0.0}, x, y, w;
        T p{0.0}, q{0.0}, z{0.0}, r{0.0}, s{0.0};
        while (en >= low && en <= m)
        {
            iter = 0;
            na = en - 1;
            while (true)
            {
                // search for small subdiagonal element
                uint16_t l_;
                for (l_ = low; l_ < en; ++l_)
                {
                    l = en + low - l_;
                    if (std::abs(hes(l, l - 1)) <= _MACH_EPS * (std::abs(hes(l - 1, l - 1)) + std::abs(hes(l, l)))) break;
                }
                l = en + low - l_;

                x = hes(en, en);
                if (l == en)
                {  // Found one eigen value
                    eigenValuesR(en) = hes(en, en) = x + t;
                    eigenValuesI(en) = static_cast<T>(0.0);
                    count(en) = iter;
                    --en;
                    break;
                }

                y = hes(na, na);
                w = hes(en, na) * hes(na, en);

                if (l == na)
                {  // Found two eigen values
                    p = (y - x) / 2.0;
                    q = p * p + w;
                    z = std::sqrt(std::abs(q));
                    x = hes(en, en) = x + t;
                    hes(na, na) = y + t;
                    count(en) = -iter;
                    count(na) = iter;
                    if (q >= static_cast<T>(0.0))
                    {  // Real part of eigen value
                        z = p < static_cast<T>(0.0) ? p - z : p + z;
                        eigenValuesR(na) = x + z;
                        eigenValuesR(en) = s = x - w / z;
                        eigenValuesI(na) = eigenValuesI(en) = static_cast<T>(0.0);
                        x = hes(en, na);
                        r = std::sqrt(x * x + z * z);

                        // Compute eigen vector
                        p = x / r;
                        q = z / r;
                        for (uint16_t j{na}; j < m; ++j)
                        {
                            z = hes(na, j);
                            hes(na, j) = q * z + p * hes(en, j);
                            hes(en, j) = q * hes(en, j) - p * z;
                        }

                        for (uint16_t i{0}; i <= en; ++i)
                        {
                            z = hes(i, na);
                            hes(i, na) = q * z + p * hes(i, en);
                            hes(i, en) = q * hes(i, en) - p * z;
                        }

                        for (uint16_t i{low}; i <= high; ++i)
                        {
                            z = eigenVectors(i, na);
                            eigenVectors(i, na) = q * z + p * eigenVectors(i, en);
                            eigenVectors(i, en) = q * eigenVectors(i, en) - p * z;
                        }
                    }
                    else
                    {
                        eigenValuesR(na) = eigenValuesR(en) = x + p;
                        eigenValuesI(na) = z;
                        eigenValuesI(en) = -z;
                    }

                    en -= 2;
                    break;
                }  // end if l == na

                if (iter >= _maxIter)
                {
                    count(en) = _maxIter + 1;
                    return true;  // reached max iterations
                }

                if (iter != 0 && iter % 10 == 0)
                {
                    t += x;
                    for (uint16_t i{low}; i <= en; ++i) hes(i, i) -= x;
                    s = std::abs(hes(en, na)) + std::abs(hes(na, en - 2));
                    x = y = static_cast<T>(0.75) * s;
                    w = static_cast<T>(-0.4375) * s * s;
                }

                ++iter;

                for (uint16_t n_{static_cast<uint16_t>(l + 1)}; n_ <= en - 1; ++n_)
                {
                    n = en - 1 - n_;
                    z = hes(n, n);
                    r = x - z;
                    s = y - z;
                    p = (r * s - w) / hes(n + 1, n) + hes(n, n + 1);
                    q = hes(n + 1, n + 1) - z - r - s;
                    r = hes(n + 2, n + 1);
                    s = std::abs(p) + std::abs(q) + std::abs(r);
                    p /= s;
                    q /= s;
                    r /= s;
                    if (n == l) break;
                    if (n == 0) return true;
                    if (std::abs(hes(n, n - 1)) * (std::abs(q) + std::abs(r)) <=
                        _MACH_EPS * std::abs(p) * (std::abs(hes(n - 1, n - 1)) + std::abs(z) + std::abs(hes(n + 1, n + 1))))
                        break;
                }

                for (uint16_t i{static_cast<uint16_t>(n + 2)}; i <= en; ++i) hes(i, i - 2) = static_cast<T>(0.0);
                for (uint16_t i{static_cast<uint16_t>(n + 3)}; i <= en; ++i) hes(i, i - 3) = static_cast<T>(0.0);

                for (uint16_t k{n}; k <= na; ++k)
                {  // QR step for rows 1 to en and cols m to en
                    if (k != n)
                    {
                        p = hes(k, k - 1);
                        q = hes(k + 1, k - 1);
                        r = (k != na) ? hes(k + 2, k - 1) : static_cast<T>(0.0);
                        x = std::abs(p) + std::abs(q) + std::abs(r);
                        if (x == static_cast<T>(0.0)) continue;
                        p /= x;
                        q /= x;
                        r /= x;
                    }
                    s = norm(Matrix<3, 1, T>{p, q, r});
                    if (p < static_cast<T>(0.0)) s = -s;

                    if (k != n) { hes(k, k - 1) = -s * x; }
                    else if (l != n) { hes(k, k - 1) = -hes(k, k - 1); }
                    p += s;
                    x = p / s;
                    y = q / s;
                    z = r / s;
                    q /= p;
                    r /= p;

                    for (j = k; j < m; ++j)
                    {  // modify rows
                        p = hes(k, j) + q * hes(k + 1, j);
                        if (k != na)
                        {
                            p += r * hes(k + 2, j);
                            hes(k + 2, j) -= p * z;
                        }
                        hes(k + 1, j) -= p * y;
                        hes(k, j) -= p * x;
                    }

                    j = (k + 3 < en) ? k + 3 : en;
                    for (uint16_t i{0}; i <= j; ++i)
                    {  // modify cols
                        p = x * hes(i, k) + y * hes(i, k + 1);
                        if (k != na)
                        {
                            p += z * hes(i, k + 2);
                            hes(i, k + 2) -= p * r;
                        }
                        hes(i, k + 1) -= p * q;
                        hes(i, k) -= p;
                    }

                    // Eigen Vectors
                    for (uint16_t i{low}; i <= high; ++i)
                    {
                        p = x * eigenVectors(i, k) + y * eigenVectors(i, k + 1);
                        if (k != na)
                        {
                            p += z * eigenVectors(i, k + 2);
                            eigenVectors(i, k + 2) -= p * r;
                        }
                        eigenVectors(i, k + 1) -= p * q;
                        eigenVectors(i, k) -= p;
                    }
                }
            }
        }

        // transform eigen vectors
        if (transformEigenVectors(hes, eigenValuesR, eigenValuesI, eigenVectors, low, high)) return true;
        return false;
    }

    template <uint16_t m, typename T>
    bool transformEigenVectors(Matrix<m, m, T>& hes, Matrix<m, 1, T>& eigenValuesR, Matrix<m, 1, T>& eigenValuesI, Matrix<m, m, T>& eigenVectors, uint16_t low,
                               uint16_t high) noexcept
    {
        uint16_t l, n, en, na;
        T p, q, r{0.0}, s{0.0}, t, w, x, y, z{0.0};
        T ra, sa, vr, vi, norm{0.0};

        // Find the norm of hes
        for (uint16_t i = 0; i < m; ++i)
        {
            for (uint16_t j = i; j < m; ++j) norm += std::abs(hes(i, j));
        }

        if (norm == static_cast<T>(0.0)) return true;

        // Transform back
        for (uint16_t en_{1}; en_ <= m; ++en_)
        {
            en = m - en_;
            p = eigenValuesR(en);
            q = eigenValuesI(en);
            na = en - 1;
            if (q == 0.0)
            {
                n = en;
                hes(en, en) = 1.0;
                uint16_t i;
                for (uint16_t i_{0}; i_ <= na && na < m; ++i_)
                {  // Check for underflow on na
                    i = na - i_;
                    w = hes(i, i) - p;
                    r = hes(i, en);
                    for (uint16_t j = n; j <= na; ++j) r += hes(i, j) * hes(j, en);
                    if (eigenValuesI(i) < 0.0)
                    {
                        z = w;
                        s = r;
                    }
                    else
                    {
                        n = i;
                        if (eigenValuesI(i) == 0.0) { hes(i, en) = -r / ((w != 0.0) ? w : _MACH_EPS * norm); }
                        else
                        {
                            x = hes(i, i + 1);
                            y = hes(i + 1, i);
                            q = (eigenValuesR(i) - p) * (eigenValuesR(i) - p) + eigenValuesI(i) * eigenValuesI(i);
                            hes(i, en) = t = (x * s - z * r) / q;
                            hes(i + 1, en) = std::abs(x) > std::abs(z) ? (-r - w * t) / x : (-s - y * t) / z;
                        }
                    }
                }
            }
            else if (q < 0.0)
            {
                n = na;
                if (std::abs(hes(en, na)) > std::abs(hes(na, en)))
                {
                    hes(na, na) = -(hes(en, en) - p) / hes(en, na);
                    hes(na, en) = -q / hes(en, na);
                }
                else
                {
                    std::complex<T> temp1(-hes(na, en), 0.0);
                    std::complex<T> temp2(hes(na, na) - p, q);
                    std::complex<T> c = temp1 / temp2;
                    hes(na, na) = std::real(c);
                    hes(na, en) = std::imag(c);
                }

                hes(en, na) = 1.0;
                hes(en, en) = 0.0;
                uint16_t i;
                for (uint16_t i_{1}; i_ <= na; ++i_)
                {
                    i = na - i_;
                    w = hes(i, i) - p;
                    ra = hes(i, en);
                    sa = 0.0;
                    for (uint16_t j = n; j <= na; ++j)
                    {
                        ra += hes(i, j) * hes(j, na);
                        sa += hes(i, j) * hes(j, en);
                    }

                    if (eigenValuesI(i) < 0.0)
                    {
                        z = w;
                        r = ra;
                        s = sa;
                    }
                    else
                    {
                        n = i;
                        if (eigenValuesI(i) == 0.0)
                        {
                            std::complex<T> temp1(-ra, -sa);
                            std::complex<T> temp2(w, q);
                            std::complex<T> c = temp1 / temp2;
                            hes(i, na) = std::real(c);
                            hes(i, en) = std::imag(c);
                        }
                        else
                        {
                            x = hes(i, i + 1);
                            y = hes(i + 1, i);
                            vr = (eigenValuesR(i) - p) * (eigenValuesR(i) - p) + eigenValuesI(i) * eigenValuesI(i) - q * q;
                            vi = 2.0 * q * (eigenValuesI(i) - p);
                            if (vr == 0.0 && vi == 0.0) vr = _MACH_EPS * norm * (std::abs(w) + std::abs(q) + std::abs(x) + std::abs(y) + std::abs(z));
                            {
                                std::complex<T> temp1(x * r - z * ra + q * sa, x * s - z * sa - q * ra);
                                std::complex<T> temp2(vr, vi);
                                std::complex<T> c = temp1 / temp2;
                                hes(i, na) = std::real(c);
                                hes(i, en) = std::imag(c);
                            }

                            if (std::abs(x) > std::abs(z) + std::abs(q))
                            {
                                hes(i + 1, na) = (-ra - w * hes(i, na) + q * hes(i, en)) / x;
                                hes(i + 1, en) = (-sa - w * hes(i, en) - q * hes(i, na)) / x;
                            }
                            else
                            {
                                std::complex<T> temp1(-r - y * hes(i, na), -s - y * hes(i, en));
                                std::complex<T> temp2(z, q);
                                std::complex<T> c = temp1 / temp2;
                                hes(i + 1, na) = std::real(c);
                                hes(i + 1, en) = std::imag(c);
                            }
                        }
                    }
                }
            }
        }

        for (uint16_t i = 0; i < m; ++i)
        {
            if (i < low || i > high)
                for (uint16_t k = i + 1; k < m; ++k) eigenVectors(i, k) = hes(i, k);
        }

        uint16_t j;
        for (uint16_t j_{low}; j_ != m; ++j_)
        {
            j = m - 1 - j_;
            n = j <= high ? j : high;
            if (eigenValuesI(j) < 0.0)
            {
                l = j - 1;
                for (uint16_t i = low; i <= high; ++i)
                {
                    y = 0.0;
                    z = 0.0;
                    for (uint16_t k = low; k <= n; ++k)
                    {
                        y += eigenVectors(i, k) * hes(k, l);
                        z += eigenVectors(i, k) * hes(k, j);
                    }
                    eigenVectors(i, l) = y;
                    eigenVectors(i, j) = z;
                }
            }
            else
            {
                if (eigenValuesI(j) == 0.0)
                {
                    for (uint16_t i = low; i <= high; ++i)
                    {
                        z = 0.0;
                        for (uint16_t k = low; k <= n; ++k) z += eigenVectors(i, k) * hes(k, j);
                        eigenVectors(i, j) = z;
                    }
                }
            }
        }

        return false;
    }

    int computeBasis() noexcept
    {
        float x{1.0}, eins{1.0}, b{1.0};

        while ((x + eins) - x == eins) x *= 2.0;
        while ((x + b) == x) b *= 2.0;

        return static_cast<int>((x + b) - x);
    }

    template <uint16_t m, typename T>
    bool normalizeEigenVectors(Matrix<m, m, T>& eigenVectors, Matrix<m, 1, T>& eigenValuesI) noexcept
    {
        if (m < 1) return true;

        float maxI, tr, ti;
        for (uint16_t j{0}; j < m; ++j)
        {
            if (eigenValuesI(j) == 0.0)
            {
                maxI = eigenVectors(0, j);
                for (uint16_t i{1}; i < m; ++i)
                {
                    if (std::abs(eigenVectors(i, j)) > std::abs(maxI)) maxI = eigenVectors(i, j);
                }

                if (maxI != 0.0)
                {
                    maxI = 1.0 / maxI;
                    for (uint16_t i{0}; i < m; ++i) eigenVectors(i, j) *= maxI;
                }
            }
            else
            {
                tr = eigenVectors(0, j);
                ti = eigenVectors(0, j + 1);
                for (uint16_t i{1}; i < m; ++i)
                {
                    std::complex<T> temp1(eigenVectors(i, j), eigenVectors(i, j + 1));
                    std::complex<T> temp2(tr, ti);
                    if (std::norm(temp1) > std::norm(temp2))
                    {
                        tr = eigenVectors(i, j);
                        ti = eigenVectors(i, j + 1);
                    }
                }
                if (tr != 0.0 || ti != 0.0)
                {
                    for (uint16_t i{0}; i < m; ++i)
                    {
                        std::complex<T> temp1(eigenVectors(i, j), eigenVectors(i, j + 1));
                        std::complex<T> temp2(tr, ti);
                        std::complex<T> c = temp1 / temp2;
                        eigenVectors(i, j) = std::real(c);
                        eigenVectors(i, j + 1) = std::imag(c);
                    }
                }
                ++j;
            }
        }

        return false;
    }

    int _maxIter;
};

}  // namespace Math
}  // namespace VN

#endif  // VN_EIGENDECOMPOSITION_HPP_
