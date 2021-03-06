#pragma once

#include <vector>

class Vector : public std::vector<float> {
public:
    Vector(unsigned int size, float value) : vector(size, value) {}
    Vector(unsigned int size) : vector(size) {}
    Vector() {}

    Vector& operator-=(const Vector& v);

    Vector& operator+=(const Vector& v);
};

class RowView;
float dot(const RowView& v1, const Vector& v2);

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator+(const Vector& v, float f);

Vector operator-(const Vector& v1, const Vector& v2);

Vector operator*(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v, float f);

class Matrix;
Vector operator*(const Matrix& m, const Vector& vec);

float sigma(float f);
Vector sigma(const Vector& v);
Vector sigmaDeriv(const Vector& v);

