#ifndef Magnum_EigenIntegration_Integration_h
#define Magnum_EigenIntegration_Integration_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
@brief

@todo Transform, Quaternion, Rotation, Translation, Transform<n>

@todoc mention stl debug output
*/

#include <Magnum/Math/RectangularMatrix.h>
#include <Eigen/Core>

namespace Magnum {

namespace Math { namespace Implementation {

template<std::size_t size> struct BoolVectorConverter<size, Eigen::Array<bool, int(size), 1>> {
    static BoolVector<size> from(const Eigen::Array<bool, size, 1>& other) {
        BoolVector<size> out{NoInit};
        for(std::size_t i = 0; i != size; ++i)
            out.set(i, other(i, 0));
        return out;
    }

    static Eigen::Array<bool, size, 1> to(const BoolVector<size>& other) {
        /** @todo is there a NoInit tag or something? */
        Eigen::Array<bool, size, 1> out;
        for(std::size_t i = 0; i != size; ++i)
            out(i, 0) = other[i];
        return out;
    }
};

template<std::size_t size, class T> struct VectorConverter<size, T, Eigen::Array<T, int(size), 1>> {
    static Vector<size, T> from(const Eigen::Array<T, size, 1>& other) {
        Vector<size, T> out{NoInit};
        for(std::size_t i = 0; i != size; ++i)
            out[i] = other(i, 0);
        return out;
    }

    static Eigen::Array<T, size, 1> to(const Vector<size, T>& other) {
        /** @todo is there a NoInit tag or something? */
        Eigen::Array<T, size, 1> out;
        for(std::size_t i = 0; i != size; ++i)
            out(i, 0) = other[i];
        return out;
    }
};

template<std::size_t size, class T> struct VectorConverter<size, T, Eigen::Matrix<T, int(size), 1>> {
    static Vector<size, T> from(const Eigen::Matrix<T, size, 1>& other) {
        Vector<size, T> out{NoInit};
        for(std::size_t i = 0; i != size; ++i)
            out[i] = other(i, 0);
        return out;
    }

    static Eigen::Matrix<T, size, 1> to(const Vector<size, T>& other) {
        /** @todo is there a NoInit tag or something? */
        Eigen::Matrix<T, size, 1> out;
        for(std::size_t i = 0; i != size; ++i)
            out(i, 0) = other[i];
        return out;
    }
};

template<std::size_t cols, std::size_t rows, class T> struct RectangularMatrixConverter<cols, rows, T, Eigen::Array<T, int(rows), int(cols)>> {
    static RectangularMatrix<cols, rows, T> from(const Eigen::Array<T, rows, cols>& other) {
        RectangularMatrix<cols, rows, T> out{NoInit};
        for(std::size_t col = 0; col != cols; ++col)
            for(std::size_t row = 0; row != rows; ++row)
                out[col][row] = other(row, col);
        return out;
    }

    static Eigen::Array<T, rows, cols> to(const RectangularMatrix<cols, rows, T>& other) {
        /** @todo is there a NoInit tag or something? */
        Eigen::Array<T, rows, cols> out;
        for(std::size_t col = 0; col != cols; ++col)
            for(std::size_t row = 0; row != rows; ++row)
                out(row, col) = other[col][row];
        return out;
    }
};

template<std::size_t cols, std::size_t rows, class T> struct RectangularMatrixConverter<cols, rows, T, Eigen::Matrix<T, int(rows), int(cols)>> {
    static RectangularMatrix<cols, rows, T> from(const Eigen::Matrix<T, rows, cols>& other) {
        RectangularMatrix<cols, rows, T> out{NoInit};
        for(std::size_t col = 0; col != cols; ++col)
            for(std::size_t row = 0; row != rows; ++row)
                out[col][row] = other(row, col);
        return out;
    }

    static Eigen::Matrix<T, rows, cols> to(const RectangularMatrix<cols, rows, T>& other) {
        /** @todo is there a NoInit tag or something? */
        Eigen::Matrix<T, rows, cols> out;
        for(std::size_t col = 0; col != cols; ++col)
            for(std::size_t row = 0; row != rows; ++row)
                out(row, col) = other[col][row];
        return out;
    }
};

}}

namespace EigenIntegration {

template<class To, class From> inline To eigenCast(const From& from) {
    return from.operator To();
}

}

}

#endif
