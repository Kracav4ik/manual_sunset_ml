#pragma once

#include <math.h>

namespace ms {
    template<int N>
    class Vector {
        float _data[N];
    public:
        typedef Vector<N> SelfType;

        SelfType& operator*=(float f) {
            for (float& x: _data) {
                x *= f;
            }
            return *this;
        }

        SelfType& operator/=(float f) {
            return operator*=(1 / f);
        }


        SelfType& operator+=(const SelfType& v) {
            for (int i = 0; i < N; ++i) {
                _data[i] += v[i];
            }
            return *this;
        }

        SelfType& operator-=(const SelfType& v) {
            for (int i = 0; i < N; ++i) {
                _data[i] -= v[i];
            }
            return *this;
        }

        float* begin() {
            return _data;
        }

        float* end() {
            return _data + N;
        }

        const float* begin() const {
            return _data;
        }

        const float* end() const {
            return _data + N;
        }


        float operator[](int idx) const {
            return _data[idx];
        }

        float& operator[](int idx) {
            return _data[idx];
        }
    };

    template<int N>
    float dot(const Vector<N>& v1, const Vector<N>& v2) {
        float res = 0;

        for (int i = 0; i < N; ++i) {
            res += v2[i] * v1[i];
        }

        return res;
    }

    template<typename T>
    int idx_max(const T& v) {
        int i = 0;
        int max_i = -1;
        float max_f = -INFINITY;
        for (float f: v) {
            if (i == 0 || f > max_f) {
                max_f = f;
                max_i = i;
            }
            ++i;
        }
        return max_i;
    }

    template<int N>
    void softmax(Vector<N>& v) {
        float sum = 0;
        for (int i = 0; i < N; ++i) {
            v[i] = expf(v[i]);
            sum += v[i];
        }
        v /= sum;
    }
}

