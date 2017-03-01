#include "Vector.h"

#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "Matrix.h"


float dot(const RowView& v1, const Vector& v2) {
    float sum = 0;
    for (int i = 0; i < v2.size(); ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

Vector operator+(const Vector& v1, const Vector& v2) {
    CHECK(v1.size() != v2.size(), printf("Error: Incorrect size for V+V vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size()); crashForDebug();)
    Vector v3 = v1;
    for (int i = 0; i < v2.size(); ++i) {
        v3[i] += v2[i];
    }
    return v3;
}

Vector operator-(const Vector& v1, const Vector& v2) {
    CHECK(v1.size() != v2.size(), printf("Error: Incorrect size for V-V vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size()); crashForDebug();)
    Vector v3 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        v3[i] -= v2[i];
    }
    return v3;
}

Vector operator*(const Vector& v1, const Vector& v2) {
    CHECK(v1.size() != v2.size(), printf("Error: Incorrect size for V*V vectors vec1 size(%d) not equal vec2 size(%d)\n", v1.size(), v2.size()); crashForDebug();)
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
    CHECK(vec.size() != m.width(), printf("Error: Incorrect value for M*V vector size(%d) not equal matrix width(%d)\n", vec.size(), m.width()); crashForDebug();)
    unsigned int columnCount = m.height();
    Vector result(columnCount);
    for (int i = 0; i < columnCount; ++i) {
        result[i] = dot(m.get_row(i), vec);
    }
    return result;
}

Vector sigma(const Vector& v){
    Vector res;
    for (float el: v) {
        res.push_back(1 / (1 + expf(-el)));
    }
    return res;
}

Vector sigmaDeriv(const Vector& v){
    Vector res;
    for (float el: v) {
        res.push_back(expf(-el)/((1 + expf(-el))*(1 + expf(-el))));
    }
    return res;
}

Vector& Vector::operator-=(const Vector& v) {
    CHECK(v.size() != size(), printf("Error: Incorrect size for V-=V vector size(%d) not equal own size(%d)\n", v.size(), size()); crashForDebug();)
    for (int i = 0; i < v.size(); ++i) {
        (*this)[i] -= v[i];
    }
    return *this;
}
