#include "Matrix.h"

#include <stdio.h>
#include "utils.h"
#include <QString>

Matrix::Matrix(unsigned int width, unsigned int height)
        : _width(width), _height(height), matrix(width, Vector(height)) {
}

Matrix::Matrix(const Vector& stdvector):_width(1), _height(stdvector.size()), matrix(1) {
    matrix[0] = stdvector;
}

const Vector& Matrix::get_column(int x) const {
    CHECK(x >= width(), printf("Error: Incorrect index for column x(%d): index out of range (%d)\n", x, width()); crashForDebug();)
    return matrix[x];
}

RowView Matrix::get_row(int y) const {
    CHECK(y >= height(), printf("Error: Incorrect index for row y(%d): index out of range (%d)\n", y, height()); crashForDebug();)
    return RowView(*this, y);
}

float Matrix::get(int x, int y) const {
    CHECK(x >= width(), printf("Error: Incorrect index for get x(%d): index out of range (%d)\n", x, width()); crashForDebug();)
    CHECK(y >= height(), printf("Error: Incorrect index for get y(%d): index out of range (%d)\n", y, height()); crashForDebug();)
    return matrix[x][y];
}

void Matrix::set(int x, int y, float value) {
    CHECK(x >= width(), printf("Error: Incorrect index for set x(%d): index out of range (%d)\n", x, width()); crashForDebug();)
    CHECK(y >= height(), printf("Error: Incorrect index for set y(%d): index out of range (%d)\n", y, height()); crashForDebug();)
    matrix[x][y] = value;
}

Matrix Matrix::operator*(const Matrix& other) const{
    CHECK(other.height() != width(), printf("Error: Incorrect value for M*M other height(%d) not equal our width(%d)\n", other.height(), width()); crashForDebug();)
    Matrix result(other.width(), height());
    for (int x = 0; x < other.width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, dot(get_row(y), other.get_column(x)));
        }
    }
    return result;
}

Matrix Matrix::operator*(float num) const {
    Matrix result(width(), height());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, num * matrix[x][y]);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) {
    CHECK(other.width() != width(), printf("Error: Incorrect value for M-M other width(%d) not equal us width(%d)\n", other.width(), width()); crashForDebug();)
    CHECK(other.height() != height(), printf("Error: Incorrect value for M-M other height(%d) not equal us height(%d)\n", other.height(), height()); crashForDebug();)
    Matrix result(width(), height());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, matrix[x][y] - other[x][y]);
        }
    }
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    CHECK(other.width() != width(), printf("Error: Incorrect value for M-=M other width(%d) not equal us width(%d)\n", other.width(), width()); crashForDebug();)
    CHECK(other.height() != height(), printf("Error: Incorrect value for M-=M other height(%d) not equal us height(%d)\n", other.height(), height()); crashForDebug();)
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            matrix[x][y] -= other[x][y];
        }
    }
    return *this;
}

QString Matrix::str() const {
    QString res;
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res += QString("%1 ").arg(get(x, y));
        }
//        res += "\n";
    }
    return res;
}

QString Matrix::strForPrint() const {
    QString res;
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res += QString("%1 ").arg(get(x, y));
        }
        res += "\n";
    }
    return res;
}


const Vector& Matrix::operator[](int idx) const {
    CHECK(idx >= matrix.size(), printf("Error: Incorrect index in const M[] idx(%d): index out of range (%d)", idx, matrix.size()); crashForDebug();)
    return matrix[idx];
}

Vector& Matrix::operator[](int idx) {
    CHECK(idx >= matrix.size(), printf("Error: Incorrect index in M[] idx(%d): index out of range (%d)", idx, matrix.size()); crashForDebug();)
    return matrix[idx];
}

unsigned int Matrix::width() const {
    return _width;
}

unsigned int Matrix::height() const {
    return _height;
}

Matrix Matrix::transp() const {
    Matrix res(height(), width());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res[y][x] = matrix[x][y];
        }
    }
    return res;
}

void Matrix::fillRandf() {
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            matrix[x][y] = frand(-1, 1);
        }
    }
}

void Matrix::fill(float f) {
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            matrix[x][y] = f;
        }
    }
}

RowView::RowView(const Matrix& m, int y): m(m), y(y) {}

float RowView::operator[](int x) const { return m.get(x, y); }
