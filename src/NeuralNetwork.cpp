#include "NeuralNetwork.h"

float frand() {
    return qrand()/(float)RAND_MAX;
}

float frand(float a, float b) {
    return a + frand() * (b - a);
}

NeuralNetwork::NeuralNetwork(const NeuroVector<int>& v, const NeuroVector<float>& img):layers(v.size()), deltas(v.size()) {
    NeuroVector<float> inputData = img;
    for (int i = 0; i < v.size(); ++i) {
        Layer& currentLayer = layers[i];
        currentLayer = Layer(inputData, v[i]);
//        inputData = currentLayer.get_out();
        //    for std
        inputData = currentLayer.get_outV();
    }
}

NeuroVector<float> NeuralNetwork::output() {
//    return layers.last().get_out();
//    for std
    return layers.data()[layers.size() -1].get_outV();
}

Layer NeuralNetwork::getLast() {
    return layers[layers.size()-1];
}

void NeuralNetwork::process(int expect) {
    vector<float> y(layers[layers.size() - 1].get_outV().size());
    y[expect] = 1;
    vector<float> currentDelta = (getLast().get_outV() - y) * sigmaDeriv(getLast().get_z());
    for (int i = deltas.size() - 1; i > 0; --i) {
        deltas[i] = currentDelta;
        layers[i].coef.transpW();
        currentDelta = ((layers[i].coef) * currentDelta) * sigmaDeriv(layers[i].get_z());
    }
    deltas[0] = currentDelta;
}
