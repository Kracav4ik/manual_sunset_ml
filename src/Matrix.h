#pragma once

#include "Vector.h"
#include <QString>

class Matrix;
class RowView {
    const Matrix& m;
    int y;
public:
    RowView(const Matrix& m, int y);
    float operator[](int x) const;
};

class Matrix {
    std::vector<Vector> matrix;
    unsigned int _width;
    unsigned int _height;
public:
    Matrix(unsigned int width, unsigned int height);
    Matrix(const Vector& stdvector);

    const Vector& get_column(int x) const;

    RowView get_row(int y) const;

    float get(int x, int y) const;

    void set(int x, int y, float value);

    Matrix operator*(const Matrix& other) const;

    Matrix operator*(float num) const;

    Matrix operator-(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    const Vector& operator[](int idx) const;
    Vector& operator[](int idx);

    unsigned int width() const;
    unsigned int height() const;

    Matrix transp() const;

    void fillRandf();
    void fill(float f);

    QString str() const;
    QString strForPrint() const;

    Matrix() {}
};
