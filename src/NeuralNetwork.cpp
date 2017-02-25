#include "NeuralNetwork.h"

float frand() {
    return qrand()/(float)RAND_MAX;
}

float frand(float a, float b) {
    return a + frand() * (b - a);
}

NeuralNetwork::NeuralNetwork(const NeuroVector<int>& v, const NeuroVector<float>& img):layers(v.size()) {
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
