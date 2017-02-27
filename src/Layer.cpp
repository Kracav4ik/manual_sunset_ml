#include <QVector>
#include "Layer.h"

float scalar(const Vector& v) {
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

float dot(const Vector& v1, const Vector& v2) {
    return scalar(v1 * v2);
}

Vector operator+(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for sum vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        crashForDebug(); // for debug
    }
    Vector v3 = v1;
    for (int i = 0; i < v2.size(); ++i) {
        v3[i] += v2[i];
    }
    return v3;
}

Vector operator-(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for sum vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        crashForDebug(); // for debug;
    }
    Vector v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] -= v2[i];
    }
    return v3;
}

Vector operator*(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        printf("Error: Incorrect size for multiply vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size());
        crashForDebug(); // for debug
    }
    Vector v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] *= v2[i];
    }
    return v3;
}

Vector operator*(const Vector& v, float f) {
    if (v.empty()){
        printf("Warning: Your vector is empty in multiply vector by number\n");
        return v;
    }
    Vector v2 = v;
    for (int i = 0; i < v.size(); ++i) {
        v2[i] *= f;
    }
    return v2;
}

Vector operator/(const Vector& v, float f) {
    return v * (1/f);
}

Vector sigma(Vector v){
    Vector res;
    for (float el: v) {
        res.push_back(1 / (1 + expf(-el)));
    }
    return res;
}

Vector sigmaDeriv(Vector v){
    Vector res;
    for (float el: v) {
        res.push_back(expf(-el)/((1 + expf(-el))*(1 + expf(-el))));
    }
    return res;
}

Matrix::Matrix(unsigned int width, unsigned int height)
        : _width(width), _height(height), matrix(width, Vector(height)) {
}

Matrix::Matrix(const Vector& stdvector):_width(1), _height(stdvector.size()), matrix(1) {
    matrix[0] = stdvector;
}

Vector Matrix::get_row(int x) const {
    if (x > width()){
        printf("Error: Incorrect index for row x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    Vector res;
    for (int y = 0; y < matrix[x].size(); ++y) {
        res.push_back(matrix[x][y]);
    }
    return res;
}

Vector Matrix::get_column(int y) const {
    if (y > height()){
        printf("Error: Incorrect index for column y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    Vector res;
    for (int x = 0; x < matrix.size(); ++x) {
        const float& element = matrix[x][y];
        res.push_back(element);
    }
    return res;
}

float Matrix::get(int x, int y) const {
    if (x > width()){
        printf("Error: Incorrect index for get x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    if (y > height()){
        printf("Error: Incorrect index for get y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    return matrix[x][y];
}

void Matrix::set(int x, int y, float value) {
    if (x > width()){
        printf("Error: Incorrect index for set x(%d)\nindex out of range", x);
        crashForDebug(); // for debug
    }
    if (y > height()){
        printf("Error: Incorrect index for set y(%d)\nindex out of range", y);
        crashForDebug(); // for debug
    }
    matrix[x][y] = value;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if (other.width() == height()) {
        Matrix result(width(), other.height());
        for (int x = 0; x < width(); ++x) {
            for (int y = 0; y < other.height(); ++y) {
                result.set(x, y, scalar(get_row(x) * other.get_column(y)));
            }
        }
        return result;
    }

    if (other.height() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        crashForDebug(); // for debug
    }
    Matrix result(other.width(), height());
    for (int x = 0; x < other.width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, scalar(other.get_row(x) * get_column(y)));
        }
    }
    return result;
}

Matrix Matrix::operator*(float num) const {
    Matrix result(width(), height());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, num * matrix[x][y]);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) {
    if (other.width() != width()) {
        printf("Error: Incorrect value for multiply other height(%d) not equal us width(%d)\n", other.height(), width());
        crashForDebug(); // for debug
    }
    Matrix result(width(), height());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            result.set(x, y, matrix[x][y] - other[x][y]);
        }
    }
    return result;}

QString Matrix::str() const {
    QString res;
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res += QString("%1 ").arg(get(x, y));
        }
        res += "\n";
    }
    return res;
}
Vector Matrix::operator[](int idx) const {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        crashForDebug(); // for debug
    }

    return matrix[idx];
}

void crashForDebug() { int i = 1 / 0; }

Vector& Matrix::operator[](int idx) {
    if (idx > matrix.size() - 1) {
        printf("Error: Incorrect index in '[]' idx(%d)\nindex out of range", idx);
        crashForDebug(); // for debug
    }

    return matrix[idx];
}

unsigned int Matrix::width() const {
    return _width;
}

unsigned int Matrix::height() const {
    return _height;
}

Matrix Matrix::transp() const {
    Matrix res(height(), width());
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            res[y][x] = matrix[x][y];
        }
    }
    return res;
}

void Matrix::fillRandf() {
    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            matrix[x][y] = frand(-1, 1);
        }
    }
}


Vector operator*(const Matrix& m, const Vector& vec) {
    unsigned int columnCount = m.height();
    Vector result(columnCount);
    for (int i = 0; i < columnCount; ++i) {
        result[i] = dot(m.get_column(i), vec);
    }
    return result;
}

Vector Layer::get_out() {
    return a;
}

Vector Layer::get_z() {
    return z;
}

void Layer::process(Vector inpt) {
    inp = inpt;
    z = coef * inp + bias;
    a = sigma(z);
}

void Layer::init(unsigned int inp_size, unsigned int neurons_count) {
    inp.resize(inp_size);
    bias.resize(neurons_count);
    z.resize(neurons_count);
    a.resize(neurons_count);

    coef = Matrix(inp_size, neurons_count);
    coef.fillRandf();

    for (float& f : bias) {
        f = frand(-1, 1);
    }
}

void Layer::correctInformation(Vector delta, float alpha) {
    coef = coef - Matrix(delta) * Matrix(inp).transp() * alpha;
    bias = bias - delta * alpha;
}
