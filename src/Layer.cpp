#include <QVector>
#include "Layer.h"

#include "utils.h"

const Vector& Layer::get_out() {
    return a;
}
const Vector& Layer::get_z() {
    return z;
}

void Layer::process(const Vector& inpt) {
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

void Layer::correctInformation(const Vector& delta, float alpha) {
    coef -= Matrix(delta) * Matrix(inp).transp() * alpha;
    bias -= delta * alpha;
}
