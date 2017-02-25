#pragma once

#include <vector>
#include <QtCore/QString>

using namespace std;

float frand();

float scalar(const vector<float>& v);

vector<float> operator+(const vector<float>& v1, const vector<float>& v2);

vector<float> operator*(const vector<float>& v, float f);

vector<float> operator*(const vector<float>& v, float f);

vector<float> true_expf(vector<float> v);

vector<float> operator+(const vector<float>& v, float f);

class Matrix {
    vector<vector<float>> matrix;
    int _width;
    int _height;
public:
    Matrix(int width, int height);
    Matrix(const vector<vector<float>>& stdmatrix);

    void clear();

    vector<float> get_row(int x) const;

    vector<float> get_column(int y) const;

    float get(int x, int y) const;
    float& get(int x, int y);

    void set(int x, int y, float value);
    Matrix operator*(const Matrix& other);

    vector<float> operator[](int idx) const;
    vector<float>& operator[](int idx);

    int width() const;
    int height() const;

    QString str();

    Matrix() {}
};

class Layer {
    Matrix coef;
    vector<float> bias;
    vector<float> inp;
    vector<float> out;
public:
    Layer(const vector<float>& inpt, int count_neuron_in_layer);

    Layer(const QVector<float>& inpt, int count_neuron_in_layer);

    void recount_out();

    QVector<float> get_out();

    vector<float> get_outV();

    Layer(){};

};
