#pragma once

#include "Matrix.h"


class Layer {
    Vector bias;
    Vector inp;
    Vector z;
    Vector a;
public:
    Matrix coef;

    Vector get_out();

    Vector get_z();

    Layer(){};

    void init(unsigned int inp_size, unsigned int neurons_count);

    void process(Vector inpt);
    void correctInformation(Vector delta, float alpha);
};
