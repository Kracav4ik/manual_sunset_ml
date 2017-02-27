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

Vector Matrix::get_row(int x) const {
    if (x > width()){
        printf("Error: Incorrect index for row x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    Vector res;
    for (int y = 0; y < matrix[x].size(); ++y) {
        res.push_back(matrix[x][y]);
    }
    return res;
}

Vector Matrix::get_column(int y) const {
    if (y > height()){
        printf("Error: Incorrect index for column y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    Vector res;
    for (int x = 0; x < matrix.size(); ++x) {
        const float& element = matrix[x][y];
        res.push_back(element);
    }
    return res;
}

float Matrix::get(int x, int y) const {
    if (x > width()){
        printf("Error: Incorrect index for get x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    if (y > height()){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    return matrix[x][y];
}

void Matrix::set(int x, int y, float value) {
    if (x > width()){
        printf("Error: Incorrect index for set x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    if (y > height()){
        printf("Error: Incorrect index for set y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    matrix[x][y] = value;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if (other.width() == height()) {
        Matrix result(width(), other.height());
        for (int x = 0; x < width(); ++x) {
            for (int y = 0; y < other.height(); ++y) {
                result.set(x, y, scalar(get_row(x) * other.get_column(y)));
            }
        }
        return result;
    }

    if (other.height() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        crashForDebug(); // for debug
    }
    Matrix result(other.width(), height());
    for (int x = 0; x < other.width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, scalar(other.get_row(x) * get_column(y)));
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
    if (other.width() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        crashForDebug(); // for debug
    }
    Matrix result(width(), height());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, matrix[x][y] - other[x][y]);
        }
    }
    return result;}

QString&& Matrix::str() const {
    QString res;
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res += QString("%1 ").arg(get(x, y));
        }
        res += "\n";
    }
    return std::move(res);
}
Vector Matrix::operator[](int idx) const {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        crashForDebug(); // for debug
    }

    return matrix[idx];
}

Vector& Matrix::operator[](int idx) {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        crashForDebug(); // for debug
    }

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