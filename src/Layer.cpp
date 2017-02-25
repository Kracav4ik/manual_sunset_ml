#include "Layer.h"

float scalar(const vector<float>& v) {
    if (v.empty()){
        printf("Warning: Your vector is empty in cancer scalar\n");
        return 0;
    }
    float res = 0;
    for (const float& el: v) {
        res += el;
    }
    return res;
}

vector<float> operator+(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for sum vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        exit(-1);
    }
    vector<float> v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] += v2[i];
    }
    return v3;
}

vector<float> operator*(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for multiply vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        exit(-1);
    }
    vector<float> v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] *= v2[i];
    }
    return v3;
}

vector<float> operator*(const vector<float>& v, float f) {
    if (v.empty()){
        printf("Warning: Your vector is empty in multiply vector by number\n");
        return v;
    }
    vector<float> v2 = v;
    for (int i = 0; i < v.size(); ++i) {
        v2[i] *= f;
    }
    return v2;
}

Matrix::Matrix(int width, int height)
        : _width(width), _height(height) {
    clear();
}

Matrix::Matrix(const vector<vector<float>>& stdmatrix) :_width(stdmatrix.size()), _height(stdmatrix[0].size()), matrix(stdmatrix){}

void Matrix::clear() {
    matrix = vector<vector<float>>();
    for (int __ = 0; __ < width(); ++__) {
        vector<float> xx;
        for (int _ = 0; _ < height(); ++_) {
            xx.push_back(0);
        }
        matrix.push_back(xx);
    }
}

vector<float> Matrix::get_row(int x) const {
    if (x > width() - 1){
        printf("Error: Incorrect index for row x(%d)\nindex out of range", x);
        exit(-1);
    }
    vector<float> res;
    for (int y = 0; y < matrix[x].size(); ++y) {
        res.push_back(matrix[x][y]);
    }
    return res;
}

vector<float> Matrix::get_column(int y) const {
    if (y > height() - 1){
        printf("Error: Incorrect index for column y(%d)\nindex out of range", y);
        exit(-1);
    }
    vector<float> res;
    for (int x = 0; x < matrix.size(); ++x) {
        const float& element = matrix[x][y];
        res.push_back(element);
    }
    return res;
}

float Matrix::get(int x, int y) const {
    if (x > width() - 1){
        printf("Error: Incorrect index for get x(%d)\nindex out of range", x);
        exit(-1);
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        exit(-1);
    }
    return matrix[x][y];
}

float& Matrix::get(int x, int y) {
    if (x > width() - 1){
        printf("Error: Incorrect index for get x(%d)\nindex out of range", x);
        exit(-1);
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        exit(-1);
    }
    float& res = matrix[x][y];
    return res;
}

void Matrix::set(int x, int y, float value) {
    if (x > width() - 1){
        printf("Error: Incorrect index for set x(%d)\nindex out of range", x);
        exit(-1);
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for set y(%d)\nindex out of range", y);
        exit(-1);
    }
    matrix[x][y] = value;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (other.height() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        exit(-1);
    }
    Matrix result(height(), other.width());
    for (int x = 0; x < other.width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, scalar(other.get_row(x) * get_column(y)));
        }
    }
    return result;
}

QString Matrix::str() {
    QString res;
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res += QString("%1").arg(get(x, y));
        }
        res += "\n";
    }
    return res;
}

vector<float> Matrix::operator[](int idx) const {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        exit(-1);
    }

    return matrix[idx];
}

vector<float>& Matrix::operator[](int idx) {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        exit(-1);
    }

    return matrix[idx];
}

int Matrix::width() const {
    return _width;
}
int Matrix::height() const {
    return _height;
}


Layer::Layer(const vector<float>& inpt, int count_neuron_in_layer)
        : inp(inpt), coef(count_neuron_in_layer, inpt.size()) {
    for (int i = 0; i < count_neuron_in_layer; ++i) {
        coef[i] = inp * frand();
        out[i] = scalar(inp * frand());
    }
    out = coef[0] + bias;
}

void Layer::recount_out() {
    for (int i = 0; i < coef.width(); ++i) {
        coef[i] = inp * frand();
        out[i] = scalar(inp * frand());
    }
    out = coef[0] + bias;
}

vector<float> Layer::get_out() {
    return out;
}
