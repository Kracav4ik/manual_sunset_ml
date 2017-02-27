#include "Vector.h"

#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "Matrix.h"


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

Vector operator*(const Matrix& m, const Vector& vec) {
    unsigned int columnCount = m.height();
    Vector result(columnCount);
    for (int i = 0; i < columnCount; ++i) {
        result[i] = dot(m.get_column(i), vec);
    }
    return result;
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
