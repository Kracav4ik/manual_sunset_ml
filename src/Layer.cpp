#include <QVector>
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
        int i = 1/0; // for degug
    }
    vector<float> v3 = v1;
    for (int i = 0; i < v2.size(); ++i) {
        v3[i] += v2[i];
    }
    return v3;
}

vector<float> operator-(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for sum vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        int i = 1/0; // for degug;
    }
    vector<float> v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] -= v2[i];
    }
    return v3;
}

vector<float> operator*(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for multiply vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        int i = 1/0; // for degug
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

vector<float> operator/(const vector<float>& v, float f) {
    return v * (1/f);
}

vector<float> operator/(float f, const vector<float>& v) {
    if (v.empty()){
        printf("Warning: Your vector is empty in multiply vector by number\n");
        return v;
    }
    vector<float> v2 = v;
    for (int i = 0; i < v.size(); ++i) {
        if (v2[i] != 0){
            v2[i] = f/v2[i];
        }
    }
    return v2;
}

vector<float> sigma(vector<float> v){
    vector<float> res;
    for (float el: v) {
        res.push_back(1 / (1 + expf(-el)));
    }
    return res;
}

vector<float> sigmaDeriv(vector<float> v){
    vector<float> res;
    for (float el: v) {
        res.push_back(expf(-el)/((1 + expf(-el))*(1 + expf(-el))));
    }
    return res;
}

vector<float> operator+(const vector<float>& v, float f){
    if (v.empty()){
        printf("Warning: Your vector is empty in multiply vector by number\n");
        return v;
    }
    vector<float> v2 = v;
    for (int i = 0; i < v.size(); ++i) {
        v2[i] += f;
    }
    return v2;
}
vector<float> operator+(float f, const vector<float>& v){
    return v + f;
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
        int i = 1/0; // for degug
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
        int i = 1/0; // for degug
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
        int i = 1/0; // for degug
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        int i = 1/0; // for degug
    }
    return matrix[x][y];
}

float& Matrix::get(int x, int y) {
    if (x > width() - 1){
        printf("Error: Incorrect index for get x(%d)\nindex out of range", x);
        int i = 1/0; // for degug
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        int i = 1/0; // for degug
    }
    float& res = matrix[x][y];
    return res;
}

void Matrix::set(int x, int y, float value) {
    if (x > width() - 1){
        printf("Error: Incorrect index for set x(%d)\nindex out of range", x);
        int i = 1/0; // for degug
    }
    if (y > height() - 1){
        printf("Error: Incorrect index for set y(%d)\nindex out of range", y);
        int i = 1/0; // for degug
    }
    matrix[x][y] = value;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (other.height() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        int i = 1/0; // for degug
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
            res += QString("%1 ").arg(get(x, y));
        }
        res += "\n";
    }
    return res;
}

vector<float> Matrix::operator[](int idx) const {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        int i = 1/0; // for degug
    }

    return matrix[idx];
}

vector<float>& Matrix::operator[](int idx) {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        int i = 1/0; // for degug
    }

    return matrix[idx];
}

int Matrix::width() const {
    return _width;
}
int Matrix::height() const {
    return _height;
}

void Matrix::transpW() {
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < x; ++y) {
            float tmp = matrix[x][y];
            matrix[x][y] = matrix[y][x];
            matrix[y][x] = tmp;
        }
    }
    int i = width();
    _width = height();
    _height = i;
}

vector<float> Matrix::operator*(const vector<float>& vec) {
    vector<float> res;
    if (vec.size() == height()){
        for (int y = 0; y < height(); ++y) {
            res.push_back(scalar(get_column(y)));
        }
    } else if (vec.size() == width()){
        for (int x = 0; x < width(); ++x) {
            res.push_back(scalar(get_row(x)));
        }
    } else{
        int i = 1/0; // for degug;
    }
    return res * vec;
}


Layer::Layer(const vector<float>& inpt, int count_neuron_in_layer)
        : inp(inpt), coef(count_neuron_in_layer, inpt.size()) {
    for (int i = 0; i < count_neuron_in_layer; ++i) {
        coef[i] = inp * frand();
        a.push_back(scalar(inp * frand())/inp.size());
    }

    for (int i = 0; i < a.size(); ++i) {
        bias.push_back(frand());
    }

    z = a + bias;
    a = sigma(z);
}

Layer::Layer(const QVector<float>& inpt, int count_neuron_in_layer)
        : inp(inpt.toStdVector()), coef(count_neuron_in_layer, inpt.size()) {
    for (int i = 0; i < count_neuron_in_layer; ++i) {
        coef[i] = inp * frand();
        a.push_back(scalar(inp * frand())/inp.size());
    }

    for (int i = 0; i < a.size(); ++i) {
        bias.push_back(frand());
    }

    z = a + bias;
    a = sigma(z);
}

void Layer::recount_out() {
    for (int i = 0; i < coef.width(); ++i) {
        coef[i] = inp * frand();
        a[i] = scalar(inp * frand());
    }
    a = coef[0] + bias;
}

vector<float> Layer::get_outV() {
    return a;
}

QVector<float> Layer::get_out() {
    return QVector<float>(a.size(), a.data()[0]);
}

vector<float> Layer::get_z() {
    return z;
}
