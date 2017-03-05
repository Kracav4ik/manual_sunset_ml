#pragma once

#include "Matrix.h"


class Layer {
public:
    Vector bias;
    Vector inp;
    Vector z;
    Vector a;
    Matrix coef;

    const Vector& get_out();

    const Vector& get_z();

    Layer(){};

    void init(unsigned int inp_size, unsigned int neurons_count);

    void process(const Vector& inpt);
    void correctInformation(const Vector& delta, float alpha);
};
