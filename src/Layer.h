#pragma once

#include <vector>
#include <QString>

class Vector : public std::vector<float> {
public:
    Vector(unsigned int size) : vector(size) {}
    Vector() {}
};

class Matrix;
float frand(float from, float to);

float scalar(const Vector& v);

float dot(const Vector& v1, const Vector& v2);

Vector operator+(const Vector& v1, const Vector& v2);

Vector operator*(const Vector& v1, const Vector& v2);

Vector operator-(const Vector& v1, const Vector& v2);

Vector operator*(const Vector& v, float f);

Vector operator*(const Vector& v, float f);

Vector operator*(const Matrix& m, const Vector& vec);

Vector sigma(Vector v);
Vector sigmaDeriv(Vector v);

void crashForDebug();

Vector operator+(const Vector& v, float f);

class Matrix {
    std::vector<Vector> matrix;
    int _width;
    int _height;
public:
    Matrix(unsigned int width, unsigned int height);
    Matrix(const Vector& stdvector);

    Vector get_row(int x) const;

    Vector get_column(int y) const;

    float get(int x, int y) const;

    void set(int x, int y, float value);

    Matrix operator*(const Matrix& other) const;

    Matrix operator*(float num) const;

    Matrix operator-(const Matrix& other);
    Vector operator[](int idx) const;
    Vector& operator[](int idx);

    unsigned int width() const;
    unsigned int height() const;

    Matrix transp() const;

    void fillRandf();

    QString str() const;

    Matrix() {}
};

class Layer {
    Vector bias;
    Vector inp;
    Vector z;
    Vector a;
public:
    Matrix coef;

    Vector get_out();

    Vector get_z();

    Layer(){};

    void init(unsigned int inp_size, unsigned int neurons_count);

    void process(Vector inpt);
    void correctInformation(Vector delta, float alpha);
};
