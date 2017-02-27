#pragma once

#include <vector>

class Vector : public std::vector<float> {
public:
    Vector(unsigned int size) : vector(size) {}
    Vector() {}
};

float scalar(const Vector& v);

float dot(const Vector& v1, const Vector& v2);

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator+(const Vector& v, float f);

Vector operator-(const Vector& v1, const Vector& v2);

Vector operator*(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v, float f);

class Matrix;
Vector operator*(const Matrix& m, const Vector& vec);

Vector sigma(Vector v);
Vector sigmaDeriv(Vector v);

