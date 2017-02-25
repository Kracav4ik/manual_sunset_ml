#include "Layer.h"

float scalar(vector<float> v) {
    float res = 0;
    for (const float& el: v) {
        res += el;
    }
    return res;
}

vector<float> operator+(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size()) {
        return vector<float>();
    }
    vector<float> v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] += v2[i];
    }
    return v3;
}

vector<float> operator*(const vector<float>& v, float f) {
    vector<float> v2 = v;
    for (int i = 0; i < v.size(); ++i) {
        v2[i] *= f;
    }
    return v2;
}

Matrix::Matrix(int width, int height)
        : width(width), height(height) {
    clear();
}

void Matrix::clear() {
    matrix = vector<vector<float>>();
    for (int __ = 0; __ < width; ++__) {
        vector<float> xx;
        for (int _ = 0; _ < height; ++_) {
            xx.push_back(0);
        }
        matrix.push_back(xx);
    }
}

vector<float> Matrix::get_row(int x) {
    vector<float> res;
    for (int y = 0; y < matrix[x].size(); ++y) {
        res.push_back(matrix[x][y]);
    }
    return res;
}

vector<float> Matrix::get_column(int y) {
    vector<float> res;
    for (int x = 0; x < matrix.size(); ++x) {
        res.push_back(matrix[x][y]);
    }
    return res;
}

float& Matrix::get(int x, int y) {
    for (int i = 0; i < x - width + 1; ++i) {
        vector<float> vec;
        for (int j = 0; j < height; ++j) {
            vec.push_back(0);
        }
        matrix.push_back(vec);
    }
    for (int i = 0; i < y - height + 1; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[j].push_back(0);
        }
    }
    return matrix[x][y];
}

Matrix Matrix::operator*(Matrix other) {
    if (other.height != width) {
        return *this;
    }
    Matrix result(height, other.width);
    for (int x = 0; x < other.width; ++x) {
        for (int y = 0; y < height; ++y) {
            get(x, y) = scalar(other.get_row(x) + get_column(y));
        }
    }
    return result;
}

QString Matrix::str() {
    QString res;
    for (int x = 0; x < matrix.size(); ++x) {
        for (int y = 0; y < matrix[x].size(); ++y) {
            res += QString("%1").arg(matrix[x][y]);
        }
        res += "\n";
    }
    return res;
}
