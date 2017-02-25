#pragma once

#include <vector>
#include <QtCore/QString>

using namespace std;

float frand();

float scalar(vector<float> v);

vector<float> operator+(const vector<float>& v1, const vector<float>& v2);

vector<float> operator*(const vector<float>& v, float f);

class Matrix {
    vector<vector<float>> matrix;
    int width;
    int height;
public:
    Matrix(int width, int height);

    void clear();

    vector<float> get_row(int x);

    vector<float> get_column(int y);

    float& get(int x, int y);

    Matrix operator*(Matrix other);

    vector<float> operator[](int idx) {
        if (matrix.empty()) {
            return vector<float>();
        }
        if (idx > matrix.size() - 1) {
            return matrix[matrix.size() - 1];
        }

        return matrix[idx];
    }

    QString str();

    Matrix() {}
};

class Layer {
    Matrix coef;
    vector<float> bias;
    vector<float> inp;
    vector<float> out;

    Layer(const vector<float>& inpt, int count_neuron_in_layer)
            : inp(inpt), coef(inpt.size(), count_neuron_in_layer) {
        for (int i = 0; i < count_neuron_in_layer; ++i) {
            coef[i] = inp * frand();
        }
    }


};
