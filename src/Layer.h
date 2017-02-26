#pragma once

#include <vector>
#include <QString>

using namespace std;
class Matrix;
float frand(float from, float to);

float scalar(const vector<float>& v);

float dot(const vector<float>& v1, const vector<float>& v2);

vector<float> operator+(const vector<float>& v1, const vector<float>& v2);

vector<float> operator*(const vector<float>& v1, const vector<float>& v2);

vector<float> operator-(const vector<float>& v1, const vector<float>& v2);

vector<float> operator*(const vector<float>& v, float f);

vector<float> operator*(const vector<float>& v, float f);

vector<float> operator*(const Matrix& m, const vector<float>& vec);

vector<float> sigma(vector<float> v);
vector<float> sigmaDeriv(vector<float> v);

void crashForDebug();

vector<float> operator+(const vector<float>& v, float f);

class Matrix {
    vector<vector<float>> matrix;
    int _width;
    int _height;
public:
    Matrix(unsigned int width, unsigned int height);
    Matrix(const vector<float>& stdvector);

    vector<float> get_row(int x) const;

    vector<float> get_column(int y) const;

    float get(int x, int y) const;

    void set(int x, int y, float value);

    Matrix operator*(const Matrix& other) const;

    Matrix operator*(float num) const;

    Matrix operator-(const Matrix& other);
    vector<float> operator[](int idx) const;
    vector<float>& operator[](int idx);

    unsigned int width() const;
    unsigned int height() const;

    Matrix transp() const;

    void fillRandf();

    QString str() const;

    Matrix() {}
};

class Layer {
    vector<float> bias;
    vector<float> inp;
    vector<float> z;
    vector<float> a;
public:
    Matrix coef;

    vector<float> get_out();

    vector<float> get_z();

    Layer(){};

    void init(unsigned int inp_size, unsigned int neurons_count);

    void process(vector<float> inpt);
    void correctInformation(vector<float> delta, float alpha);
};
