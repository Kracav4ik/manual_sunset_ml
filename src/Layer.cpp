#include <QVector>
#include "Layer.h"

#include "utils.h"

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
