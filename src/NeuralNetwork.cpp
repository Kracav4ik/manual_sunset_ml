#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(unsigned int inputSize, const std::vector<unsigned int>& sizesVec)
        : layers(sizesVec.size()), deltas(sizesVec.size()) {
    for (int i = 0; i < sizesVec.size(); ++i) {
        layers[i].init(inputSize, sizesVec[i]);
        inputSize = sizesVec[i];
    }
}

const Vector& NeuralNetwork::output() {
//    return layers.last().get_out();
//    for std
    return layers.back().get_out();
}

void NeuralNetwork::process(Vector inputData) {
    for (int i = 0; i < layers.size(); ++i) {
        layers[i].process(inputData);
        inputData = layers[i].get_out();
    }
}

void NeuralNetwork::train(int expect, const Vector& x, float alpha) {
    Vector y(layers.back().get_out().size());
    y[expect] = 1;

    Vector currentDelta = (layers.back().get_out() - y);
    for (int i = deltas.size() - 1; i > 0; --i) {
        deltas[i] = currentDelta;
        currentDelta = (layers[i].coef.transp() * currentDelta);
    }
    deltas[0] = currentDelta;

    for (int l = 0; l < layers.size(); ++l) {
        layers[l].correctInformation(deltas[l], alpha);
    }

    process(x);
}
